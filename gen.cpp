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



int main(int argc, char const *argv[])
{
    while (1)
    {
        string input;
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
                    cout << "Fam " << word << endl; //insert family vertex
                else if (previous_word == "Husband")
                    cout << "Hubby " << word << endl; //introdce Husband person node to family
                else if (previous_word == "Wife")
                    cout << "Wifey " << word << endl; //insert wife person node to family
                else if (previous_word == "Child")
                    cout << "Childe " << word << endl; //insert child node to family
                else if (previous_word == "Relate")
                    relate_first = word;
                else if (word != "Family" || word != "Husband" || word != "Wife" || word != "Child" || word != "Relate")
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
    }
    return 0;
}
