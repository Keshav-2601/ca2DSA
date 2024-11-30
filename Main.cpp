#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <cctype>
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

vector<string> splitCSVLine(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

void createIndex(const vector<vector<string>>& data, int fieldIndex) {
    map<string, int> index; 
    for (const auto& row : data) {
        if (fieldIndex >= 0 && fieldIndex < row.size()) {
            index[row[fieldIndex]]++;
        }
    }


    cout << "Index created based on field #" << fieldIndex << ":";
    /*for (const auto& [key, count] : index) {
        cout << key << ": " << count << " rows";
    }*/
}

void filterData(const vector<vector<string>>& data, int fieldIndex, const string& value) {
    cout << "Rows where field #" << fieldIndex << " matches '" << value << "':\n";
    for (const auto& row : data) {
        if (fieldIndex >= 0 && fieldIndex < row.size() && row[fieldIndex] == value) {
            for (const auto& col : row) {
                cout << col << " ";
            }
            cout << endl;
        }
    }
}

void processTextFile() {
    TreeMap<char, BinaryTree<string>> wordMap;

    ifstream inputFile("ca2DSAtextfile.txt");
    if (!inputFile) {
        cout << "Error: Could not open file.";
        return;
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
        cout << "1. Display all letters with words.";
        cout << "2. Display all words associated with a letter.";
        cout << "3. Back to main menu.";
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
                cout << "No words found for the letter '" << letter << " ";
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.";
        }
    }
}


void processCSVFile() {
    ifstream file("DSAca2CSV.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open CSV file.";
        return;
    }

    vector<vector<string>> data;
    string line;

    getline(file, line);
    vector<string> headers = splitCSVLine(line);

    
    while (getline(file, line)) {
        data.push_back(splitCSVLine(line));
    }
    file.close();

    while (true) {
        cout << "Options:";
        cout << "1. Display field names.";
        cout << "2. Create an index based on a field.";
        cout << "3. Filter data by field value.";
        cout << "4. Back to main menu.";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Field names:";
            for (int i = 0; i < headers.size(); i++) {
                cout << i << ": " << headers[i] << " ";
            }
        }
        else if (choice == 2) {
            cout << "Enter the field index to create an index: ";
            int fieldIndex;
            cin >> fieldIndex;

            if (fieldIndex >= 0 && fieldIndex < headers.size()) {
                createIndex(data, fieldIndex);
            }
            else {
                cout << "Invalid field index.";
            }
        }
        else if (choice == 3) {
            cout << "Enter the field index to filter by: ";
            int fieldIndex;
            cin >> fieldIndex;

            cout << "Enter the value to filter by: ";
            string value;
            cin.ignore();
            getline(cin, value);

            if (fieldIndex >= 0 && fieldIndex < headers.size()) {
                filterData(data, fieldIndex, value);
            }
            else {
                cout << "Invalid field index.\n";
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.";
        }
    }
}

int main() {
    while (true) {
        cout << "Choose an option:";
        cout << "1. Process text file (Stage 2).";
        cout << "2. Process CSV data (Stage 4).";
        cout << "3. Exit.";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            processTextFile();
        }
        else if (choice == 2) {
            processCSVFile();
        }
        else if (choice == 3) {
            cout << "Exiting the program. Goodbye!";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.";
        }
    }

    return 0;
}
