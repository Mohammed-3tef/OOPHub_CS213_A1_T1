// File: A1_T1_20231143.cpp
// Purpose: .........
// Author: Mohammed Atef Abd El-Kader
// ID: 20231143
// TA:
// Date: 8 Oct 2024
// Version: 3.0

#include <bits/stdc++.h>
using namespace std;

// This function to check if the input is a number.
bool isNumber(const string &string) {
    for (char const &ch : string) {
        if (!isdigit(ch)) return false;
    }
    return true;
}

// This function returns the index of the word in the given string.
int indexWord (string str, string word) {
    int index = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == word[0]) {
            int j = 0;
            while (j < word.size() && i < str.size() && str[i] == word[j]) {
                i++, j++;
            }
            if (j == word.size()) return index;
        }
        if (str[i] == ' ') index++;
    }
    return -1;
}

// This function splits a string into words and stores them in a vector.
vector<pair<int, string>> splitWords(int num, string str) {
    vector<pair<int, string>> words;
    string word;
    for (char i : str) {
        if (!isspace(i)) word += i;
        else {
            if (!word.empty()) {
                words.emplace_back(num, word);
                word.clear();
            }
        }
    }
    if (!word.empty()) words.emplace_back(num, word);
    return words;
}

// This function extracts and returns punctuation from a string,
// removing it from the original.
string Punctuations (string& str) {
    string result;
    for (int i = str.size()-1 ; i >= 0; --i) {
        if (ispunct(str[i])) {
            result.insert(result.begin(), str[i]);
            str.erase(str.begin()+i);
        }
        else break;
    }
    return result;
}

string convertPronounsToGenderInclusive (string str) {
    vector<string> arr;
    string init, result;

    // Adding the words to the vector and remove spaces.
    for (char i : str) {
        if (isspace(i)) {
            arr.push_back(init);
            init.clear();
        }
        else init += i;
    }
    if (!init.empty()) arr.push_back(init);  // Add the last word if any.

    // This loop replaces male pronouns in an array with gender-inclusive alternatives,
    // reattaches any extracted punctuation, and builds the final result string.
    for (int i = 0; i < arr.size(); ++i) {
        string mark = Punctuations(arr[i]);

        if (arr[i] == "He" || arr[i] == "he") arr[i] += " or she";
        else if (arr[i] == "His" || arr[i] == "his") {
            arr[i] += " or her";
            if (!mark.empty()) arr[i] += 's';  // Handle possessive 'his' punctuation.
        }
        else if (arr[i] == "Him" || arr[i] == "him") arr[i] += " or her";
        else if (arr[i] == "Himself" || arr[i] == "himself") arr[i] += " or herself";

        // Adding the punctuation to the word.
        if (!mark.empty()) arr[i] += mark;

        // Adding the word to the result.
        result += arr[i];

        // Add a space between words, except after the last word.
        if (i != arr.size() -1) result += " ";
    }
    return result;
}

void addNewPlayer (vector<pair<string, int>>& players, string newPlayer = "", int newScore = 0) {
    players.emplace_back(newPlayer, newScore);

    // Sort the players by score in descending order, and by name in ascending order.
    sort(players.begin(), players.end(), [](auto& a, auto& b) {
        return a.second != b.second ? a.second > b.second : a.first < b.first;
    });
    if (players.size() > 10) players.pop_back();
    cout << "Added Successfully." << endl << endl;
}

void printTop10(vector<pair<string, int>>& players) {
    cout << "The Top 10 are:" << endl;
    for(auto &[player, score] : players) {
        cout << "  - " << player << " -> " << score << endl;
    }
    cout << endl;
}

void searchPlayer(vector<pair<string, int>>& players, string newPlayer = ""){
    bool found = false;
    for(auto &[player, score] : players) {
        if (newPlayer == player) {
            cout << "The " << newPlayer <<"'s highest score = " << score << endl << endl;
            found = true;
            break;
        }
    }

    // If the player doesn't exist in the list.
    if (!found) cout << "This Player Doesn't Exist..." << endl << endl;
}

void playerScores(vector<pair<string, int>>& players) {
    cout << setw(40) << "Welcome To Manage Player Scores Program." << endl << endl;
    while (true) {
        cout << "Please select an option by entering the corresponding number to proceed." << endl;
        cout << " (1) Add a new player and score." << endl;
        cout << " (2) Print the top 10 players." << endl;
        cout << " (3) Find the highest score to specific player." << endl;
        cout << " (4) Exit program." << endl;
        cout << "Enter Your Choice :";
        string menuChoice; getline(cin, menuChoice);
        cout << endl;

        // If the user want to add a new player and his score.
        if (menuChoice == "1") {
            cout << "Enter the player's name :";
            string newPlayer; getline(cin, newPlayer);
            string oldScore;
            while (true) {
                cout << "Enter the player's score :";
                getline(cin, oldScore);
                if (isNumber(oldScore)) {

                    // Convert the string to an integer.
                    int newScore = stoi(oldScore);
                    addNewPlayer(players, newPlayer, newScore);
                    break;
                }

                // If the user enters an invalid score.
                else cout << "Enter A Valid Number (No Chars, No Punctuations and No Spaces)..." << endl << endl;
            }
        }

        // If the user want to print the top 10 players.
        else if (menuChoice == "2") {

            // If the list is empty.
            if (players.empty()) cout << "There Are No Players On The List." << endl << endl;
            else printTop10(players);
        }

        // If the user wants to find the highest score to specific player.
        else if (menuChoice == "3") {

            // If the list is empty.
            if (players.empty()) cout << "There Are No Players On The List." << endl << endl;
            else {
                cout << "Enter the player's name :";
                string newPlayer; getline(cin, newPlayer);
                searchPlayer(players, newPlayer);
            }
        }

        // If the user wants to exit the program.
        else if (menuChoice == "4") {
            cout << " ===>> Thanks For Using Manage Player Scores Program..." << endl;
            cout << endl;
            break;
        }

        // If the user enters an invalid choice.
        else cout << "Please Enter A Valid Choice (from 1 to 4)..." << endl << endl;
    }
}

void readFromTextFile (string protoType, string firstFilePath, string secondFilePath) {
    ifstream file1(firstFilePath);
    ifstream file2(secondFilePath);
    string line1, line2;
    if (file1.is_open() && file2.is_open()) {

        // If the user chooses character by character comparison.
        if (protoType == "Char") {
            int lineNum = 0;

            while (getline(file1, line1) && getline(file2, line2)) {
                lineNum++;
                if (line1 != line2) {
                    cout << "The Difference found at line " << lineNum << ":\n";
                    cout << " - File 1: " << line1 << endl;
                    cout << " - File 2: " << line2 << endl << endl;
                    return;
                }
            }

            if (file1.eof() && file2.eof()) cout << "The Two Files Are Identical (Character by character)..." << endl << endl;
            else cout << "The Two Files Are Not The Same Size..." << endl << endl;
        }

        // If the user chooses word by word comparison.
        else if (protoType == "String") {
            vector<pair<int ,string>> words1, words2;
            int numLine = 0;

            // Extracting words from lines and storing with line numbers for text comparison.
            while (getline(file1, line1)) {
                numLine++;
                words1 = splitWords(numLine, line1);
            }
            numLine = 0;
            while (getline(file2, line2)) {
                numLine++;
                words2 = splitWords(numLine, line2);
            }

            // If the two files are not the same size.
            if (words1.size() != words2.size()) {
                cout << "The Two Files Are Not The Same Size..." << endl << endl;
                return;
            }

            // If the two files are the same size.
            for (int i = 0; i < words1.size(); ++i) {
                if (words1[i].second != words2[i].second) {
                    // Clear EOF flag.
                    file1.clear(), file2.clear();

                    // Reset file pointer to the beginning.
                    file1.seekg(0), file2.seekg(0);

                    int currentLine = 0;
                    while (getline(file2, line2) && getline(file1, line1)) {
                        currentLine++;
                        if (currentLine == words1[i].first) {
                            cout << "The Difference found at line " << currentLine << ", word " << indexWord(line1, words1[i].second) +1 << ":\n";
                            cout << "The Difference Words are: (" << words1[i].second << ") & (" << words2[i].second << ")\n";
                            cout << " - File 1: " << line1 << endl;
                            cout << " - File 2: " << line2 << endl << endl;
                            return;
                        }
                    }
                }
            }
            cout << "The Two Files Are Identical (Word by word)..." << endl << endl;
        }
        // Close the files
        file1.close();
        file2.close();
    }

    // If the user enters an invalid file path.
    else if (!file1.is_open() && file2.is_open()) cout << "The First File Doesn't Exist..." << endl << endl;
    else if (file1.is_open() && !file2.is_open()) cout << "The Second File Doesn't Exist..." << endl << endl;
    else cout << "The Two Files Don't Exist..." << endl << endl;
}

void fileComparison() {
    cout << setw(40) << "Welcome To File Comparison Program." << endl << endl;
    while (true) {
        cout << "Please select an option by entering the corresponding number to proceed." << endl;
        cout << " (1) Character by character comparison." << endl;
        cout << " (2) Word by word comparison." << endl;
        cout << " (3) Exit program." << endl;
        cout << "Enter Your Choice :";
        string menuChoice; getline(cin, menuChoice);
        cout << endl;

        // If the user chooses character by character comparison.
        if (menuChoice == "1") {
            cout << "Enter the first file path :";
            string textFile1; getline(cin, textFile1);
            cout << "Enter the second file path :";
            string textFile2; getline(cin, textFile2);
            readFromTextFile("Char", textFile1, textFile2);
        }

        // If the user chooses word by word comparison.
        else if (menuChoice == "2") {
            cout << "Enter the first file path :";
            string textFile1; getline(cin, textFile1);
            cout << "Enter the second file path :";
            string textFile2; getline(cin, textFile2);
            readFromTextFile("String", textFile1, textFile2);
        }

        // If the user wants to exit the program.
        else if (menuChoice == "3") {
            cout << " ===>> Thanks For Using File Comparison Program..." << endl;
            cout << endl;
            break;
        }

        // If the user enters an invalid choice.
        else cout << "Please Enter A Valid Choice (from 1 to 4)..." << endl << endl;
    }
}

int main() {
    vector<pair<string, int>> players;
    cout << setw(35) << "Ahlan Ya User Ya Habibi.." << endl;
    cout << "Welcome to our application! This menu will guide you through various options to perform specific tasks." << endl;
    while (true) {
        cout << "Please select what program do you want." << endl;
        cout << " (1) Convert Pronouns To Gender Inclusive Program." << endl;
        cout << " (2) Manage Player Scores Program." << endl;
        cout << " (3) Problem 3." << endl;
        cout << " (4) File Comparison Program." << endl;
        cout << " (5) Exit application." << endl;
        cout << "Enter Your Choice :";
        string menuChoice; getline(cin, menuChoice);
        cout << endl;

        // If the user chooses, Convert Pronouns To Gender Inclusive program.
        if (menuChoice == "1") {
            cout << setw(50) << "Welcome To Convert Pronouns To Gender Inclusive program." << endl << endl;
            while (true) {
                cout << "Please select an option by entering the corresponding number to proceed." << endl;
                cout << " (1) Enter A New Message." << endl;
                cout << " (2) Exit program." << endl;
                cout << "Enter Your Choice :";
                string choice;
                getline(cin, choice);
                cout << endl;

                // If the user wants to enter a new message.
                if (choice == "1") {
                    cout << "Enter Your Message:";
                    string message; getline(cin, message);
                    cout << "The New Message is: " << convertPronounsToGenderInclusive(message) << endl << endl;
                }

                // If the user wants to exit the program.
                else if (choice == "2") {
                    cout << " ===>> Thanks For Using Convert Pronouns To Gender Inclusive Program..." << endl;
                    cout << endl;
                    break;
                }

                // If the user enters an invalid choice.
                else cout << "Please Enter A Valid Choice (from 1 to 2)..." << endl << endl;
            }
        }

        // If the user chooses, Manage Player Scores program.
        else if (menuChoice == "2") {
            playerScores(players);
        }

        // If the user chooses, Convert Pronouns To Gender Inclusive program.
        else if (menuChoice == "3") {
            cout << "Problem 3" << endl << endl;
        }

        // If the user chooses, File Comparison program.
        else if (menuChoice == "4") {
            fileComparison();
        }

        // If the user wants to exit the application.
        else if (menuChoice == "5") {
            cout << " ===>> Thanks For Using Our Application..." << endl;
            cout << " ===>> See You Later..." << endl;
            break;
        }

        // If the user enters an invalid choice.
        else cout << "Please Enter A Valid Choice (from 1 to 5)..." << endl << endl;
    }
    return 0;
}