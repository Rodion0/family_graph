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

//TODO Figuire out error handling
int main(int argc, char const *argv[])
{
    while (1)
    {
        string input;
        cout << "Please enter input:" << endl;
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
                    cout << "Family " << word << endl; //insert family vertex
                if (previous_word == "Husband")
                    cout << "Husband " << word << endl; //introdce Husband person node to family
                if (previous_word == "Wife")
                    cout << "Wife " << word << endl; //insert wife person node to family
                if (previous_word == "Child")
                    cout << "Child " << word << endl; //insert child node to family
                previous_word = word;
            }
            else
            {
                previous_word = word;
                previous_word = word;
                if (!relate_first.empty())
                {
                    cout << "Relate " << relate_first << " " << word << endl;
                    relate_first = "";
                }
                continue;
            }
        }
    }
    return 0;
}
