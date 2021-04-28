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
using namespace std;

const int HUSBAND = 0;
const int WIFE = 1;

class familyTree
{
private:
    vector<vector<int>> tree;
    vector<int> husbands;
    vector<int> wives;
    vector<int> children;

public:
    familyTree();
    void insertTree(string family_id, vector<int> family);
    void insertHusband(string husband_id) { husbands[stoi(husband_id)]++; }
    void insertWife(string wife_id) { wives[stoi(wife_id)]++; }
    void insertChild(string children_id) { children[stoi(children_id)]++; }
};

familyTree::familyTree()
{
    husbands.assign(100, 0);
    wives.assign(100, 0);
    children.assign(100, 0);
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
    cout << "Family " << family_id << " has huband " << family[HUSBAND] << ", wife " << family[WIFE] << ", and children ";
    for (auto i : family)
    {
        cout << i << " ";
    }
    cout << "." << endl;
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
                    cout << "Related " << relate_first << " " << word << endl; // Relate these guys
                    relate_first = "";
                }
            }
        }
        tree.insertTree(family_id, family);
    }
    return 0;
}
