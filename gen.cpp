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
    vector<int> family_ids;

public:
    familyTree();
    void insertTree(string family_id, string husband_id, string wife_id, vector<int> child_id, vector<int> family);
    void insertHusband(vector<int> &family, string husband_id);
    void insertWife(vector<int> &family, string wife_id);
    void insertChild(vector<int> &family, string children_id);
    void relate(int id1, int id2);
    bool connected(int id1, int id2);
    int findRoot(int id);
    void unionRoots(int id1, int id2);
    void bfs(int sourceId, int destinationID, vector<int> &path);
    void printPath(int id1, int id2);
};

familyTree::familyTree()
{
    tree.resize(NUMBER_OF_FAMILIES, vector<int>(NUMBER_OF_FAMILIES));
    husbands.resize(NUMBER_OF_FAMILIES);
    wives.resize(NUMBER_OF_FAMILIES);
    children.resize(NUMBER_OF_FAMILIES);
    family_ids.resize(NUMBER_OF_FAMILIES);
}

void familyTree::insertHusband(vector<int> &family, string husband_id)
{
    //cout << "Husband ID in insertHusband: " << husband_id << endl;
    family.emplace(family.begin(), stoi(husband_id));
    //cout << "Husband is good" << endl;
}

void familyTree::insertWife(vector<int> &family, string wife_id)
{
    //cout << "Wife ID in insertWife: " << wife_id << endl;
    family.emplace(family.begin() + 1, stoi(wife_id));
    //cout << "Wife is good" << endl;
}

void familyTree::insertChild(vector<int> &family, string children_id)
{
    //cout << "Child ID in inertChildren: " << children_id << endl;
    family.push_back(stoi(children_id));
    //cout << "CHild is good" << endl;
}

void familyTree::insertTree(string family_id, string husband_id, string wife_id, vector<int> child_id, vector<int> family)
{
    //cout << husband_id << " " << wife_id << endl;
    if (husbands[family[HUSBAND]] > 0 && stoi(husband_id) != 0)
    {
        cout << "\t Husband " << family[HUSBAND] << " is already wed." << endl;
        return;
    }
    else if (wives[family[WIFE]] > 0 && stoi(wife_id) != 0)
    {
        cout << "\t Wife " << family[WIFE] << " is already wed." << endl;
        return;
    }
    else if (family_ids[stoi(family_id)] > 0 && stoi(family_id) != 0)
    {
        cout << "\t Family " << family_id << " is already inserted." << endl;
        return;
    }
    //cout << "Parents created" << endl;
    for (int i = 0; i < child_id.size(); i++)
    {
        if (children[child_id[i]] > 0 && child_id[i] != 0)
        {
            cout << "\t Child " << child_id[i] << " is already parented." << endl;
            return;
        }
    }

    //cout << "New Value Created ";
    //cout << "Husband ID: " << husband_id << endl;
    husbands[stoi(husband_id)]++;
    //cout << "Husband incremented" << endl;
    wives[stoi(wife_id)]++;
    family_ids[stoi(family_id)]++;
    //cout << "Wife is incremented" << endl;
    for (auto i : child_id)
    {
        children[i]++;
    }
    //cout << "All vakues have been incremented" << endl;
    for (int i = 0; i < tree[stoi(family_id)].size(); i++)
    {
        tree[stoi(family_id)][i] = family[i];
    }

    //tree.insert((tree.begin() + stoi(family_id)), family);
    //cout << "Family is inserted into tree" << endl;
    cout << "Family " << family_id << " has husband " << family[HUSBAND] << ", wife " << family[WIFE] << ", and children";
    for (int i = 2; i < family.size(); i++)
    {
        if (family[i] == 0)
        {
            continue;
        }
        else
        {
            cout << " " << family[i];
        }
    }
    cout << "." << endl;
}

int familyTree::findRoot(int id)
{
    if (parents[id] == id)
    {
        return id;
    }
    return findRoot(parents[id]);
}

void familyTree::unionRoots(int id1, int id2)
{
    //cout << "I am in unionRoot" << endl;
    id1 = findRoot(id1);
    // cout << "Ive done the first find root" << endl;
    id2 = findRoot(id2);
    //cout << "I've done the second find root" << endl;
    //cout << id1 << " " << id2 << endl;
    if (id1 != id2)
    {
        parents[id2] = id1;
    }
}

bool familyTree::connected(int id1, int id2)
{
    parents.resize(NUMBER_OF_FAMILIES);
    //Do the Union Find
    for (int i = 0; i < NUMBER_OF_FAMILIES; i++)
    {
        parents[i] = i;
    }
    //cout << "Pushed back all the parents" << endl;
    for (int i = tree.size() - 1; i > 0; i--)
    {
        for (int j = tree[i].size() - 1; j > 0; j--)
        {
            unionRoots(tree[i][j], tree[i][j - 1]);
        }
    }
    //cout << "woo union roots worked" << endl;
    return parents[id1] == parents[id2];
}

void familyTree::bfs(int sourceId, int destinationID, vector<int> &path)
{
    vector<int> queue;
    vector<bool> discovered(NUMBER_OF_FAMILIES);
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
                discovered[tree[first][i]] = true;
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

    path.resize(NUMBER_OF_FAMILIES);
    bfs(id1, id2, path);

    shortPath.push_back(traveler);
    while (path[traveler] != 0)
    {
        shortPath.push_back(path[traveler]);
        traveler = path[traveler];
    }

    cout << "Relation: ";
    for (int i = 0; i < shortPath.size(); i++)
    {
        if ((i % 2) == 0)
        {
            cout << "person " << shortPath[i];
        }
        else
        {
            cout << " -> family " << shortPath[i] << " -> ";
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
    while (cin)
    {
        string input, family_id, husband_id, wife_id;
        vector<int> family(NUMBER_OF_FAMILIES), child_id(NUMBER_OF_FAMILIES);
        getline(cin, input);

        stringstream ss(input);
        string word = "";
        string previous_word = " ";
        string relate_first = "";
        while (ss >> word)
        {
            //cout << word << endl;
            if (!isdigit(previous_word[0]))
            {
                if (previous_word == "Family")
                {
                    family_id = word;
                }
                else if (previous_word == "Husband")
                {
                    husband_id = word;
                    tree.insertHusband(family, word);
                    //cout << "Inserted Husband" << endl;
                }
                else if (previous_word == "Wife")
                {
                    wife_id = word;
                    tree.insertWife(family, word);
                    //cout << "Inserted Wife" << endl;
                }
                else if (previous_word == "Child")
                {
                    //cout << "Child Word" << word << endl;
                    child_id.push_back(stoi(word));
                    //cout << "Main Child" << endl;
                    tree.insertChild(family, word);
                    //cout << "Inserted Child" << endl;
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
                    //cout << word << " " << relate_first << endl;
                    tree.relate(stoi(relate_first), stoi(word)); // Relate these guys
                    //cout << "Main Relate" << endl;
                    relate_first = "";
                }
            }
        }
        if (!husband_id.empty() && !wife_id.empty())
        {
            tree.insertTree(family_id, husband_id, wife_id, child_id, family);
        }
    }
    return 0;
}
