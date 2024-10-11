# **Assignment 1 -> Task 1**


## **Problems:**
- **Convert Pronouns To Gender Inclusive :** This name reflects the purpose of the function, which is to convert male pronouns into gender-inclusive alternatives.
- **Manage Player Scores :** Interactive menu system for adding new players, displaying the top 10 players, searching for a player's highest score, and exiting the program.
- **Fractal Pattern :** Generates a recursive fractal star pattern by halving the size at each step, with increasing indentation. The size must be a power of 2, and the user controls the horizontal shift, creating a nested, symmetrical pattern.
- **File Comparison Program :** Enables users to compare two text files, identifying differences at both character and word levels, while providing an intuitive interface for selecting comparison methods and file paths.


## **Algorithms:**

- <details>
    <summary>Convert Pronouns To Gender Inclusive Program. </summary>
    Here’s a detailed explanation of how the `maleAndFemale` function works:

    ### **Function Breakdown**:
    
    #### 1. **Punctuations Function**:
    Before diving into the main function, the helper function `Punctuations` is important to understand:
    
    ```cpp
    string Punctuations(string& str) {
        string result = "";
        for (int i = 0; i < str.size(); ++i) {
            if (ispunct(str[i])) {
                result += str[i];               // Collect punctuation.
                str.erase(str.begin() + i);      // Remove punctuation from original string.
                i--;                             // Adjust the index after deletion.
            }
        }
        return result;                           // Return the extracted punctuation.
    }
    ```
    
    - **Purpose**: This function removes punctuation from a string, stores it, and returns it while modifying the original string to remove the punctuation marks.
      - **Example**: If the input is `"He,"`, the function returns `","` and modifies the input string to `"He"`.

    #### 2. **maleAndFemale Function**:
    ```cpp
    string maleAndFemale(string str) {
        vector<string> arr;
        string init = "", result = "";
    
        // Adding the words to the vector and removing spaces.
        for (int i = 0; i < str.size(); ++i) {
            if (isspace(str[i])) {
                arr.push_back(init);       // Store each word in the array 'arr'.
                init.clear();              // Clear 'init' for the next word.
            }
            else init += str[i];           // Build the word until a space is found.
        }
        if (!init.empty()) arr.push_back(init);  // Add the last word, if any.
    
        // This loop replaces male pronouns with gender-inclusive alternatives
        // and builds the final result string.
        for (int i = 0; i < arr.size(); ++i) {
            string mark = Punctuations(arr[i]);  // Extract punctuation.
    
            // Check and replace male pronouns with gender-inclusive forms.
            if (arr[i] == "He" || arr[i] == "he") arr[i] += " or she";
            else if (arr[i] == "His" || arr[i] == "his") {
                arr[i] += " or her";
                if (!mark.empty()) arr[i] += 's';  // If "his" had punctuation like "his'", add "s".
            }
            else if (arr[i] == "Him" || arr[i] == "him") arr[i] += " or her";
            else if (arr[i] == "Himself" || arr[i] == "himself") arr[i] += " or herself";
    
            // Add punctuation back to the modified word.
            if (!mark.empty()) arr[i] += mark;
    
            // Append the processed word to the result.
            result += arr[i];
    
            // Add space between words.
            if (i != arr.size() - 1) result += " ";
        }
        return result;  // Return the fully constructed result.
    }
    ```
    
    ### **Step-by-Step Explanation**:
    
    1. **Splitting the String into Words**:
       ```cpp
       for (int i = 0; i < str.size(); ++i) {
           if (isspace(str[i])) {
               arr.push_back(init);       // Add the word to the array.
               init.clear();              // Clear 'init' for the next word.
           }
           else init += str[i];           // Build up a word character by character.
       }
       if (!init.empty()) arr.push_back(init);  // Add the last word if any.
       ```
        - The input string is processed character by character. Each word is built up (`init`), and once a space is found, the word is added to the `arr` vector.
        - This process effectively splits the string into individual words (stored in `arr`).
        - After the loop, the last word is added to the array if it exists.
    
    2. **Processing Each Word for Gender-Neutral Replacement**:
       ```cpp
       for (int i = 0; i < arr.size(); ++i) {
           string mark = Punctuations(arr[i]);  // Extract any punctuation.
    
           // Check if the current word is a male pronoun and replace accordingly.
           if (arr[i] == "He" || arr[i] == "he") arr[i] += " or she";
           else if (arr[i] == "His" || arr[i] == "his") {
               arr[i] += " or her";
               if (!mark.empty()) arr[i] += 's';  // Handle possessive 'his' punctuation.
           }
           else if (arr[i] == "Him" || arr[i] == "him") arr[i] += " or her";
           else if (arr[i] == "Himself" || arr[i] == "himself") arr[i] += " or herself";
    
           // Reattach punctuation.
           if (!mark.empty()) arr[i] += mark;
    
           // Add the processed word to the result string.
           result += arr[i];
    
           // Add a space between words, except after the last word.
           if (i != arr.size() - 1) result += " ";
       }
       ```
        - For each word in `arr`, the function first extracts and removes any punctuation using the `Punctuations` function.
        - The word is then checked to see if it matches any of the male pronouns:
            - "He" → "he or she"
            - "His" → "his or her" (possessive form also handles cases like "his'")
            - "Him" → "him or her"
            - "Himself" → "himself or herself"
        - After processing the pronouns, any punctuation previously extracted is reattached.
        - The word is then added to the final result string (`result`), with spaces added between words, except after the last word.
    
    ### **Example**:
    
    **Input**:
    ```cpp
    "He gave him his book."
    ```
    
    **Processing**:
    - Splitting the string into words: `["He", "gave", "him", "his", "book."]`
      - Replacing pronouns:
          - "He" → "He or she"
          - "him" → "him or her"
          - "his" → "his or her"
      - Reattaching punctuation:
          - "book." retains the period (".").
    
    **Final Output**:
    ```cpp
    "He or she gave him or her his or her book."
    ```
</details>

- <details>
    <summary>Manage Player Scores Program.</summary>
    Here’s a more detailed explanation of each function, including the subtle aspects, assumptions, and logic used:

    ### 1. **`void addNewPlayer` Function**
    
    ```cpp
    void addNewPlayer(vector<pair<string, int>>& players, string newPlayer = "", int newScore = 0) {
        players.emplace_back(newPlayer, newScore);
    
        sort(players.begin(), players.end(), [](auto& a, auto& b) {
            return a.second != b.second ? a.second > b.second : a.first < b.first;
        });
        if (players.size() > 10) players.pop_back();
        cout << "Added Successfully." << endl << endl;
    }
    ```
    
    #### Purpose:
    - **Add a new player with their score** into the list of players, **sort the list**, and **limit it to the top 10 players**.
    
    #### Key Details:
    1. **`players.emplace_back(newPlayer, newScore)`**:
        - This adds the new player (with name `newPlayer` and score `newScore`) to the `players` vector. The `emplace_back` function constructs the pair `newPlayer` and `newScore` directly in place, avoiding unnecessary copy or move operations, making it more efficient than `push_back` when adding pairs.
    
       2. **`sort` Function**:
           - After adding the player, the list is sorted by:
               1. **Score (Descending)**: Players with higher scores come first. The comparison `a.second > b.second` ensures that higher scores have priority.
               2. **Name (Ascending)**: In the case where two players have the same score, they are sorted by name in alphabetical order. The comparison `a.first < b.first` handles this. This ensures a deterministic order for players with the same score.
    
       3. **Limit to Top 10**:
           - If the list exceeds 10 players, the last player (the one with the lowest score) is removed with `players.pop_back()`.
    
       4. **Output**:
           - A confirmation message `"Added Successfully."` is printed.
    
    #### Assumptions:
    - **Scores are unique**: Players have unique scores; however, if there are ties in the scores, alphabetical order is used to break the tie.
      - **No validation**: This function does not validate the player name or score (e.g., it assumes the inputs are valid).
    
    ### 2. **`void printTop10` Function**
    
    ```cpp
    void printTop10(vector<pair<string, int>>& players) {
        cout << "The Top 10 are:" << endl;
        for(auto &[player, score] : players) {
            cout << "  - " << player << " -> " << score << endl;
        }
        cout << endl;
    }
    ```
    
    #### Purpose:
    - **Print the top 10 players and their scores** from the `players` list.
    
    #### Key Details:
    1. **Header**:
        - Prints `"The Top 10 are:"` to indicate the start of the list.
    
       2. **Range-based `for` loop**:
           - The loop iterates through the `players` vector. The C++ structured binding (`auto &[player, score]`) is used here to directly access each player's name (`player`) and their score (`score`).
    
       3. **Output**:
           - For each player, it prints their name followed by their score in the format: `"  - <player> -> <score>"`.
    
       4. **If Fewer Than 10 Players**:
           - If there are fewer than 10 players in the list, it prints all available players.
    
    ### 3. **`void searchPlayer` Function**
    
    ```cpp
    void searchPlayer(vector<pair<string, int>>& players, string newPlayer = "") {
        bool found = false;
        for(auto &[player, score] : players) {
            if (newPlayer == player) {
                cout << "The " << newPlayer << "'s highest score = " << score << endl << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << "This Player Doesn't Exist..." << endl << endl;
    }
    ```
    
    #### Purpose:
    - **Search for a specific player** by their name and display their highest score.
    
    #### Key Details:
    1. **Search Loop**:
        - A range-based `for` loop iterates over the `players` list. For each player, it checks if the player's name (`player`) matches the searched name (`newPlayer`).
    
       2. **Player Found**:
           - If the player is found (`newPlayer == player`), it prints `"The <newPlayer>'s highest score = <score>"` and sets the flag `found = true`. The loop then breaks out after finding the first match (since player names are unique).
    
       3. **Player Not Found**:
           - If the loop completes and no match is found (`found` remains `false`), it prints `"This Player Doesn't Exist..."`.
    
    #### Assumptions:
    - **Unique Player Names**: Player names are assumed to be unique, so once a match is found, it exits.
    
    ### 4. **`void playerScores` Function (Main Menu)**
    
    ```cpp
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
    
            if (menuChoice == "1") {
                cout << "Enter the player's name :";
                string newPlayer; getline(cin, newPlayer);
                string oldScore;
                while (true) {
                    cout << "Enter the player's score :";
                    getline(cin, oldScore);
                    if (isNumber(oldScore)) {
                        int newScore = stoi(oldScore);
                        addNewPlayer(players, newPlayer, newScore);
                        break;
                    }
                    else cout << "Enter A Valid Number (No Chars, No Punctuations and No Spaces)..." << endl << endl;
                }
            }
    
            else if (menuChoice == "2") {
                if (players.empty()) cout << "There Are No Players On The List." << endl << endl;
                else printTop10(players);
            }
    
            else if (menuChoice == "3") {
                if (players.empty()) cout << "There Are No Players On The List." << endl << endl;
                else {
                    cout << "Enter the player's name :";
                    string newPlayer; getline(cin, newPlayer);
                    searchPlayer(players, newPlayer);
                }
            }
    
            else if (menuChoice == "4") {
                cout << " ===>> Thanks For Using Manage Player Scores Program..." << endl;
                cout << endl;
                break;
            }
    
            else cout << "Please Enter A Valid Choice (from 1 to 4)..." << endl << endl;
        }
    }
    ```
    
    #### Purpose:
    - **Main menu to manage player scores**: This function provides a menu-driven interface for adding players, printing the top 10, searching for a player, and exiting the program.
    
    #### Key Details:
    1. **Menu Loop**:
        - The `while (true)` loop runs indefinitely, showing a menu with options until the user selects "Exit" (`menuChoice == "4"`).
    
       2. **Option 1: Add New Player**:
           - Prompts for the player's name and score.
           - Uses a helper function `isNumber()` (not shown) to validate the score input (ensures it’s a valid number).
           - Calls `addNewPlayer()` to add the player to the list.
    
       3. **Option 2: Print Top 10**:
           - Calls `printTop10()` to display the top players if the list is not empty. If the list is empty, it prints `"There Are No Players On The List."`.
    
       4. **Option 3: Search Player**:
           - Prompts for the player's name and calls `searchPlayer()` to display the highest score for the player. If the list is empty, it prints a message indicating there are no players.
    
       5. **Option 4: Exit**:
           - Exits the program by breaking out of the loop and printing a farewell message.
    
       6. **Invalid Input Handling**:
           - If the user enters an invalid menu choice (i.e., not "1", "2", "3", or "4"), the program prints an error message and asks for valid input.
    
</details>

- <details>
    <summary>Fractal Pattern Program.</summary>
    Here’s a detailed explanation of the functions and their underlying logic:

    ### 1. **`void pattern(int n, int i)`**
    
    This function recursively generates and prints the fractal pattern using stars (`*`). Here’s a detailed breakdown of how it works:
    
    - **Parameters**:
        - `n`: The number of stars to print in the current row.
        - `i`: Controls the indentation (shifting) of each row using spaces.
    
    #### Step-by-Step Explanation:
    - **Base Case**:
      ```cpp
      if (n <= 0) return;
      ```
      If `n` is less than or equal to 0, the function returns immediately without printing anything, which serves as the base case for recursion.
    
      - **Recursive Call**:
        ```cpp
        pattern(n/2, i);
        ```
        The function calls itself with `n` halved (`n/2`) and the same indentation (`i`). This causes the pattern to be drawn recursively for smaller values of `n`, starting from the top-most rows.
    
      - **Indentation**:
        ```cpp
        cout << string(i*2, ' ');
        ```
        This line prints spaces to shift the current row. The number of spaces printed is controlled by the value of `i`, multiplied by 2. The more recursive calls are made, the further the indentation shifts.
    
      - **Printing Stars**:
        ```cpp
        for (int j = 0; j < n; ++j) {
            j != n-1 ? cout << "* " : cout << "*\n";
        }
        ```
        This loop prints `n` stars. The ternary operator is used to print a space (`* `) after each star except for the last star in the row, which is followed by a newline (`* \n`).
    
      - **Recursive Call (Lower Half)**:
        ```cpp
        pattern(n/2, i+(n/2));
        ```
        This recursive call draws the lower half of the pattern with `n/2` stars, but with additional indentation (`i + n/2`). This creates a fractal structure where each level of recursion adds more rows of stars, with increasing indentation.
    
    ### 2. **`void fractalPattern()`**
    
    This function handles the user interaction, taking input from the user to draw the fractal pattern based on their choice. It contains the main menu system and user input validation.
    
    #### Step-by-Step Explanation:
    - **Program Welcome Message**:
      ```cpp
      cout << setw(40) << "Welcome To Fractal Pattern Program." << endl << endl;
      ```
      This prints a centered welcome message using the `setw(40)` function from the `iomanip` library to center the text.
    
      - **Main Loop**:
        The program continuously prompts the user to either draw a new pattern or exit the program, using a `while (true)` loop until the user chooses to exit.
    
      - **User Choices**:
        The program provides two options:
          - Option 1 (`menuChoice == "1"`): Draw a new fractal pattern.
          - Option 2 (`menuChoice == "2"`): Exit the program.
    
      - **Pattern Drawing**:
        When the user selects option 1, the program:
          - Prompts the user to input the **size** of the pattern (`oldSize`).
          - Validates the size to ensure it is a power of 2 (i.e., `2^n`), using the condition `log2(size) == int(log2(size))`.
          - If valid, it prompts for the number of **spaces** to shift the pattern (`oldSpaces`).
          - Once both inputs are validated, the function `pattern(size, spaces/2)` is called to draw the fractal pattern.
    
      - **Input Validation**:
        The inputs are validated using a helper function `isNumber()` (not included in the code snippet) that checks if the user's input consists only of valid digits (i.e., no characters, punctuations, or spaces).
    
      - **Exiting the Program**:
        If the user selects option 2, the program displays a thank-you message and exits the loop.
    
    ### Key Concepts:
    1. **Recursion**:
       The `pattern()` function is recursive, calling itself twice at each step—once for the top half and once for the bottom half of the fractal pattern. The recursion continues until the base case `n <= 0` is reached.
    
    2. **Fractal Pattern**:
       The stars are printed in a fractal-like structure, where the size (`n`) of the pattern at each level of recursion decreases by half (`n/2`), creating a visually recursive pattern.
    
    3. **User Input**:
       The `fractalPattern()` function takes the user's input for the size and spaces to customize the pattern's appearance, ensuring the size is a power of 2 for the fractal structure to work correctly.
    
    ### Example Output:
    For example, if the user enters `n = 4` and `i = 2`, the output might look like this:
    ```
      *
      * *
        *
      * * * *
          *
          * *
            *
    ```

    The stars are drawn recursively, and each row has more indentation than the previous one.

</details>

- <details>
    <summary>File Comparison Program.</summary>
    Here’s a detailed explanation of the functions and their underlying logic:
  
    ### 1. `indexWord` Function
    
    This function finds the index of a specified word within a string.
    
    **Detailed Explanation:**
    
    - **Purpose:** To find the position of a word in a string, measured by how many words precede it.
    
      - **Parameters:**
          - `string str`: This is the input string (e.g., a line from a text file).
          - `string word`: This is the word whose index we want to find within `str`.
    
      - **Process:**
          - **Initialization:**
              - The `index` variable is initialized to `0`. This variable tracks the word count as we traverse the string.
          - **Outer Loop (`for`):**
              - The loop iterates over each character in the string using its index `i`.
          - **Character Match Check:**
              - When the first character of the `word` matches the current character in the string (`str[i] == word[0]`):
                  - A nested loop starts (`while`) to check if the subsequent characters of `str` and `word` match.
                  - If all characters match, it means the entire word was found.
                  - If the match is complete (`j == word.size()`), the function returns the current index.
          - **Space Handling:**
              - If a space character is encountered (`if (str[i] == ' ')`), the word index is incremented (`index++`), indicating that we have moved to the next word.
          - **Return Value:**
              - If the loop completes without finding the word, `-1` is returned to signify that the word was not found.
    
    **Code Implementation:**
    ```cpp
    int indexWord(string str, string word) {
        int index = 0;
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == word[0]) {
                int j = 0;
                while (j < word.size() && i < str.size() && str[i] == word[j]) {
                    i++, j++;
                }
                if (j == word.size()) return index; // Word found
            }
            if (str[i] == ' ') index++; // Increment index for words
        }
        return -1; // Word not found
    }
    ```
    
    ### 2. `mergeVectors` Function
    
    This function merges two vectors of pairs, where each pair contains a line number and a word.
    
    **Detailed Explanation:**
    
    - **Purpose:** To combine two vectors of word pairs into one.
    
      - **Parameters:**
          - `vector<pair<int, string>>& arr1`: The first vector containing pairs of line numbers and words.
          - `vector<pair<int, string>>& arr2`: The second vector to be merged.
    
      - **Process:**
          - A new empty vector `result` is initialized.
          - The function loops through both `arr1` and `arr2`, appending each pair from both vectors to `result`.
          - Finally, it returns the combined vector.
    
    **Code Implementation:**
    ```cpp
    vector<pair<int, string>> mergeVectors(vector<pair<int, string>>& arr1, vector<pair<int, string>>& arr2) {
        vector<pair<int, string>> result; // Resulting vector
        for(auto &pair : arr1) result.push_back(pair); // Adding pairs from arr1
        for(auto &pair : arr2) result.push_back(pair); // Adding pairs from arr2
        return result; // Merged vector
    }
    ```
    
    ### 3. `splitWords` Function
    
    This function splits a given string into words and stores them alongside their respective line numbers in a vector.
    
    **Detailed Explanation:**
    
    - **Purpose:** To break a line of text into individual words, capturing each word with its line number.
    
      - **Parameters:**
          - `int num`: The line number associated with the words.
          - `string& str`: The string to be split into words.
    
      - **Process:**
          - The function initializes an empty vector `words` to store pairs of line numbers and words.
          - It uses a temporary string `word` to build each word:
              - As it iterates through each character in `str`:
                  - If the character is not a space, it appends it to `word`.
                  - When a space is encountered, it checks if `word` is non-empty:
                      - If it is, it adds the current `word` and the associated line number to `words`.
                      - Then it clears `word` to prepare for the next word.
          - After the loop, it checks if `word` is still non-empty (for the last word) and adds it to `words`.
          - Finally, it returns the vector of word pairs.
    
    **Code Implementation:**
    ```cpp
    vector<pair<int, string>> splitWords(int num, string& str) {
        vector<pair<int, string>> words; // Vector to hold word pairs
        string word; // Temporary string for current word
        for (char i : str) {
            if (!isspace(i)) word += i; // Build word character by character
            else {
                if (!word.empty()) { // If space found and word is not empty
                    words.emplace_back(num, word); // Add word with line number
                    word.clear(); // Clear for next word
                }
            }
        }
        if (!word.empty()) words.emplace_back(num, word); // Last word check
        return words; // Return vector of word pairs
    }
    ```
    
    ### 4. `readFromTextFile` Function
    
    This function reads two text files and compares their content based on the chosen comparison type.
    
    **Detailed Explanation:**
    
    - **Purpose:** To perform a comparison between two text files either character by character or word by word.
    
      - **Parameters:**
          - `string protoType`: Specifies the type of comparison ("Char" for character comparison, "String" for word comparison).
          - `string& firstFilePath`: The path to the first text file.
          - `string& secondFilePath`: The path to the second text file.
    
      - **Process:**
          - It opens both files using `ifstream`. If either file fails to open, an error message is displayed.
          - If both files are open:
              - **Character Comparison:**
                  - It reads both files line by line. If any line differs, it outputs the line number and the differing lines.
                  - If both files reach EOF without differences, it declares them identical.
              - **Word Comparison:**
                  - It reads each file line by line, splits lines into words using `splitWords`, and stores them in two separate vectors.
                  - If the vectors have different sizes, it indicates the files are not the same size.
                  - If they are the same size, it compares each word in the vectors:
                      - If a difference is found, it uses `indexWord` to find the position of the differing word and outputs relevant details.
                  - If all words match, it declares the files identical.
          - The function concludes by closing both files.
    
    **Code Implementation:**
    ```cpp
    void readFromTextFile(string protoType, string& firstFilePath, string& secondFilePath) { 
        ifstream file1(firstFilePath);
        ifstream file2(secondFilePath);
        string line1, line2;
        
        if (file1.is_open() && file2.is_open()) {
            // Character comparison logic
            if (protoType == "Char") {
                int lineNum = 0;
                while (getline(file1, line1) && getline(file2, line2)) {
                    lineNum++;
                    if (line1 != line2) {
                        cout << "The Difference found at line " << lineNum << ":\n";
                        cout << " - File 1: " << line1 << endl;
                        cout << " - File 2: " << line2 << endl << endl;
                        return; // Exit on first difference found
                    }
                }
                // Check if both files reached EOF
                if (file1.eof() && file2.eof()) cout << "The Two Files Are Identical (Character by character)..." << endl << endl;
                else cout << "The Two Files Are Not The Same Size..." << endl << endl;
            }
            // Word comparison logic
            else if (protoType == "String") {
                vector<pair<int ,string>> words1, words2; // Vectors for words
                int numLine = 0;
    
                // Read and split words from first file
                while (getline(file1, line1)) {
                    numLine++;
                    vector<pair<int ,string>> wordsInLine = splitWords(numLine, line1);
                    words1 = mergeVectors(words1, wordsInLine); // Merge words
                }
    
                numLine = 0; // Reset line number for second file
                // Read and split words from second file
                while (getline(file2, line2)) {
                    numLine++;
                    vector<pair<int ,string>> wordsInLine = splitWords(numLine, line2);
                    words2 = mergeVectors(words2, wordsInLine); // Merge words
                }
    
                // Size comparison of words
                if (words1.size() != words2.size()) {
                    cout << words1.size() << " " << words2.size() << endl;
                    cout << "The Two Files Are Not The Same Size..." << endl << endl;
                    return;
                }
    
                // Compare words
                for (int i = 0; i < words1.size(); ++i) {
                    if (words1[i].second != words2[i].
    
    second) { // If words are different
                        int position = indexWord(line1, words2[i].second); // Get position of differing word
                        cout << "Difference found at line " << words1[i].first << ", word position " << position << ":\n";
                        cout << " - File 1: " << words1[i].second << endl;
                        cout << " - File 2: " << words2[i].second << endl << endl;
                    }
                }
                cout << "The Two Files Are Identical (Word by word)..." << endl << endl;
            }
            // Close the files
            file1.close();
            file2.close();
        } else {
            cout << "Error opening one of the files..." << endl;
        }
    }
    ```
    
    ### 5. `fileComparison` Function
    
    This function orchestrates the user interaction, guiding them through the comparison process.
    
    **Detailed Explanation:**
    
    - **Purpose:** To facilitate user input and manage file comparison operations.
    
      - **Process:**
          - It welcomes the user and displays a menu of options:
              1. Compare files character by character.
              2. Compare files word by word.
              3. Exit the program.
          - The program enters a loop that continues until the user chooses to exit.
          - Based on the user’s selection:
              - If they choose option 1, it prompts them to enter file paths for character comparison and calls `readFromTextFile` with `"Char"`.
              - If option 2 is selected, it prompts for file paths for word comparison and calls `readFromTextFile` with `"String"`.
              - If option 3 is selected, the loop breaks, effectively exiting the program.
          - If an invalid choice is made, it prompts the user to enter a valid option.
    
    **Code Implementation:**
    ```cpp
    void fileComparison() {
        cout << setw(40) << "Welcome To File Comparison Program." << endl << endl;
        while (true) {
            cout << "Please select an option by entering the corresponding number to proceed." << endl;
            cout << "1. Compare files character by character." << endl;
            cout << "2. Compare files word by word." << endl;
            cout << "3. Exit." << endl;
            string menuChoice;
            cin >> menuChoice; // User choice input
    
            if (menuChoice == "1") {
                string firstFilePath, secondFilePath;
                cout << "Enter the path for the first file: ";
                cin >> firstFilePath;
                cout << "Enter the path for the second file: ";
                cin >> secondFilePath;
                readFromTextFile("Char", firstFilePath, secondFilePath); // Character comparison
            }
            else if (menuChoice == "2") {
                string firstFilePath, secondFilePath;
                cout << "Enter the path for the first file: ";
                cin >> firstFilePath;
                cout << "Enter the path for the second file: ";
                cin >> secondFilePath;
                readFromTextFile("String", firstFilePath, secondFilePath); // Word comparison
            }
            else if (menuChoice == "3") {
                cout << "Exiting program..." << endl;
                break; // Exit loop
            }
            else cout << "Please Enter A Valid Choice (from 1 to 3)..." << endl << endl; // Invalid input handling
        }
    }
    ```
    
    ### Summary of Functionality
    
    - **User Interaction:** The program starts by welcoming the user and presenting options for file comparison.
      - **File Handling:** It reads the contents of the specified files, ensuring that they are opened successfully before proceeding with comparisons.
      - **Comparison Logic:** Depending on the user's choice, the program performs character-by-character or word-by-word comparisons, outputting any differences found along with their context.
      - **Output:** It clearly communicates the results of the comparisons, informing the user whether the files are identical or detailing the differences found.
      - **Error Handling:** The program accounts for potential errors, such as failing to open files or invalid user inputs, providing appropriate feedback to the user.
</details>


## **Author:**
- **Name:** [Mohammed Atef Abd El-Kader.](https://github.com/Mohammed-3tef)
- **ID:** 20231143
- **Date:** 12 Oct 2024
- **Version:** 7.0