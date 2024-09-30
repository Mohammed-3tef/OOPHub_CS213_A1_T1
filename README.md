# **Assignment 1 -> Task 1**


## **Problems:**
- **Convert To Gender Inclusive** (This name reflects the purpose of the function, which is to convert male pronouns into gender-inclusive alternatives.)


## The Algorithms:

- <details>
    <summary>Convert To Gender Inclusive.</summary>
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