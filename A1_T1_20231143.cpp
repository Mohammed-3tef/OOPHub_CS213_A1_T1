// File: A1_T1_20231143.cpp
// Purpose: .........
// Author: Mohammed Atef Abd El-Kader
// ID: 20231143
// TA:
// Date: 8 Oct 2024
// Version: 1.0

#include <bits/stdc++.h>
using namespace std;

// This function extracts and returns punctuation from a string,
// removing it from the original.
string Punctuations (string& str) {
    string result = "";
    for (int i = 0; i < str.size(); ++i) {
        if (ispunct(str[i])) {
            result += str[i];
            str.erase(str.begin()+i);
            i--;
        }
    }
    return result;
}

string maleAndFemale (string str) {
    vector<string> arr;
    string init = "", result = "";

    // Adding the words to the vector and remove spaces.
    for (int i = 0; i < str.size(); ++i) {
        if (isspace(str[i])) {
            arr.push_back(init);
            init.clear();
        }
        else init += str[i];
    }
    if (!init.empty()) arr.push_back(init);

    // This loop replaces male pronouns in an array with gender-inclusive alternatives,
    // reattaches any extracted punctuation, and builds the final result string.
    for (int i = 0; i < arr.size(); ++i) {
        string mark = Punctuations(arr[i]);

        if (arr[i] == "He" || arr[i] == "he") arr[i] += " or she";
        else if (arr[i] == "His" || arr[i] == "his") {
            arr[i] += " or her";
            if (!mark.empty()) arr[i] += 's';
        }
        else if (arr[i] == "Him" || arr[i] == "him") arr[i] += " or her";
        else if (arr[i] == "Himself" || arr[i] == "himself") arr[i] += " or herself";

        // Adding the punctuation to the word.
        if (!mark.empty()) arr[i] += mark;

        // Adding the word to the result.
        result += arr[i];

        // Adding space between the words.
        if (i != arr.size() -1) result += " ";
    }
    return result;
}

int main() {
    cout << maleAndFemale("See an adviser and talk to him. He will guide you.") << endl;
    cout << maleAndFemale("Did you ask him?") << endl;
    cout << maleAndFemale("HE2 is a new store.") << endl;
    cout << maleAndFemale("He gave him his book.") << endl;
    cout << maleAndFemale("The dog barked.") << endl;
    cout << maleAndFemale("He, however, went to school.") << endl;
    cout << maleAndFemale("hIm walked to the store.") << endl;
    cout << maleAndFemale("He gave him his book.") << endl;
    cout << maleAndFemale("He, him, his were all used.") << endl;
    cout << maleAndFemale("He... will come soon.") << endl;
    return 0;
}