//--------------------------------------------------------------------
//				CS315-001  Assignment 5
//--------------------------------------------------------------------
// Author: Justin Hamilton
// Date: 05/05/2021
// Description: Given a text, return a word frequency count
// Assistance: We'll See
//---------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

const int HUSBAND = 0;
const int WIFE = 1;
const int NUMBER_OF_FAMILIES = 100;

class familyTree
{
private:
    vector<vector<int>> tree;
    vector<int> husbands;
    vector<int> wives;
    vector<int> children;
    vector<int> parents;

public:
    familyTree();
    void insertTree(string family_id, vector<int> family);
    void insertHusband(string husband_id) { husbands[stoi(husband_id)]++; }
    void insertWife(string wife_id) { wives[stoi(wife_id)]++; }
    void insertChild(string children_id) { children[stoi(children_id)]++; }
    void relate(int id1, int id2);
    bool connected(int id1, int id2);
    int findRoot(int id);
    void unionRoots(int id1, int id2);
    void bfs(int sourceId, int destinationID, vector<int> &path);
    void printPath(int id1, int id2);
};

familyTree::familyTree()
{
    husbands.assign(NUMBER_OF_FAMILIES, 0);
    wives.assign(NUMBER_OF_FAMILIES, 0);
    children.assign(NUMBER_OF_FAMILIES, 0);
}

void familyTree::insertTree(string family_id, vector<int> family)
{
    if (husbands[family[HUSBAND]] > 0)
    {
        cout << "Husband " << family[HUSBAND] << " is already wed." << endl;
        return;
    }
    else if (wives[family[WIFE]] > 0)
    {
        cout << "Wife " << family[WIFE] << " is already wed." << endl;
        return;
    }
    for (int i = 2; i < family.size(); i++)
    {
        if (children[family[i]] > 0)
        {
            cout << "Child " << family[i] << "already parented." << endl;
            return;
        }
    }
    tree[stoi(family_id)] = family;
    cout << "Family " << family_id << " has husband " << family[HUSBAND] << ", wife " << family[WIFE] << ", and children ";
    for (auto i : family)
    {
        cout << i << " ";
    }
    cout << "." << endl;
}

int familyTree::findRoot(int id)
{
    if (parents[id] == id)
    {
        return id;
    }
    return parents[id] = findRoot(parents[id]);
}

void familyTree::unionRoots(int id1, int id2)
{
    id1 = findRoot(id1);
    id2 = findRoot(id2);
    if (id1 != id2)
    {
        parents[id2] = id1;
    }
}

bool familyTree::connected(int id1, int id2)
{
    //Do the Union Find
    for (int i = 0; i < NUMBER_OF_FAMILIES; i++)
    {
        parents[i] = i;
    }
    for (int i = 0; i < tree.size(); i++)
    {
        for (int j = tree.size() - 1; i > 0; i++)
        {
            unionRoots(tree[i][j], tree[i][j - 1]);
        }
    }
    return parents[id1] == parents[id2];
}

void familyTree::bfs(int sourceId, int destinationID, vector<int> &path)
{
    vector<int> queue;
    vector<bool> discovered;
    discovered.assign(NUMBER_OF_FAMILIES, false);
    discovered[sourceId] = true;
    queue.push_back(sourceId);
    while (!queue.empty())
    {
        int first = queue.front();
        queue.erase(queue.begin());
        for (int i = 0; i < tree[first].size(); i++)
        {
            if (discovered[tree[first][i]] == false)
            {
                discovered[tree[first][i]] == true;
                path[tree[first][i]] = first;
                queue.push_back(tree[first][i]);
                if (tree[first][i] == destinationID)
                {
                    return;
                }
            }
        }
    }
}

void familyTree::printPath(int id1, int id2)
{
    vector<int> shortPath;
    vector<int> path;
    int traveler = id2;

    path.assign(NUMBER_OF_FAMILIES, INT_MIN);
    bfs(id1, id2, path);

    shortPath.push_back(traveler);
    while (path[traveler] != INT_MIN)
    {
        shortPath.push_back(path[traveler]);
        traveler = path[traveler];
    }

    cout << "Relation: ";
    for (int i = 0; i < path.size(); i++)
    {
        if ((i % 2) == 0)
        {
            cout << "-> family " << shortPath[i];
        }
        else
        {
            cout << "person " << shortPath[i];
        }
    }
    cout << endl;
}

void familyTree::relate(int id1, int id2)
{
    //Bool for Union Find
    bool unionConnected = connected(id1, id2);
    if (unionConnected)
    {
        printPath(id1, id2);
    }
    else
    {
        cout << "Persons " << id1 << " and " << id2 << " are not related." << endl;
    }
}

int main(int argc, char const *argv[])
{
    familyTree tree = familyTree();
    while (1)
    {
        string input, family_id, husband_id, wife_id;
        vector<int> child_id, family;
        getline(cin, input);

        stringstream ss(input);
        string word = "";
        string previous_word = "";
        string relate_first;
        while (ss >> word)
        {
            if (!isdigit(previous_word[0]))
            {
                if (previous_word == "Family")
                {
                    family_id = word;
                }
                else if (previous_word == "Husband")
                {
                    husband_id = word;
                    tree.insertHusband(husband_id);
                }
                else if (previous_word == "Wife")
                {
                    wife_id = word;
                    tree.insertWife(wife_id);
                }
                else if (previous_word == "Child")
                {
                    child_id.push_back(stoi(word));
                    tree.insertChild(word);
                }
                else if (previous_word == "Relate")
                {
                    relate_first = word;
                }
                else if (word != "Family" && word != "Husband" && word != "Wife" && word != "Child" && word != "Relate")
                {
                    cout << "Unknown command: " << word << endl;
                }
                previous_word = word;
            }
            else
            {
                previous_word = word;
                if (!relate_first.empty())
                {
                    tree.relate(stoi(word), stoi(relate_first)); // Relate these guys
                    relate_first = "";
                }
            }
        }
        tree.insertTree(family_id, family);
    }
    return 0;
}
