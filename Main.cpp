#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <filesystem>
#include "TreeMap.h"

using namespace std;


string cleanWord(const string& word) {
    string cleaned;
    for (char c : word) {
        if (isalpha(c)) {
            cleaned += tolower(c);  
        }
    }
    return cleaned;
}
int main() {
   
    TreeMap<char, BinaryTree<string>> wordMap;  

    ifstream inputFile("ca2DSAtextfile.txt");
    //cout << "Current working directory: " << std::filesystem::current_path() << endl;
    if (!inputFile) {
        cout << "Error: Could not open file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string word;
        while (ss >> word) {
            word = cleanWord(word);  
            if (!word.empty()) {
                char firstLetter = word[0];
                if (!wordMap.containsKey(firstLetter)) {
                    BinaryTree<string> newTree;
                    wordMap.put(firstLetter, newTree);
                }
                wordMap.get(firstLetter).add(word);
            }
        }
    }

    inputFile.close();

    while (true) {
        cout << "Options:";
        cout << "1. Display all letters with words.\n";
        cout << "2. Display all words associated with a letter.\n";
        cout << "3. Exit.\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            
            auto keys = wordMap.keySet();  
            cout << "Letters: ";
            keys->printInOrder();
            delete keys; 
        }
        else if (choice == 2) {
            cout << "Enter a letter: ";
            char letter;
            cin >> letter;
            letter = tolower(letter);

            if (wordMap.containsKey(letter)) {
                cout << "Words starting with '" << letter << "': ";
                wordMap.get(letter).printInOrder();
            }
            else {
                cout << "No words found for the letter '" << letter << "'." << endl;
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
