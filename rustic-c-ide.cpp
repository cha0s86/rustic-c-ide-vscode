#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// パソコンいいこと！
// Can someone share this code to bisqwit for him to read?

union pools {

    struct charpool {
        public:
            std::string charpool[64][64];
    };

    struct keywordpool {
        public:
            std::string keywordpool[64][64];
    };

    struct compiledobject {
        public:
            std::string compiledstring[64][64];
    };
};

pools::charpool parsestring(std::string codetobeparsed) {

    // Parser / Lexical analyzer
    // Parser: a computer program that breaks down text into recognized strings of characters for further analysis.

    // Create object for accessing pools
    pools::charpool charPool;

    int iterator = 0;       // Iterator for scanning and/or counting
    int wordindex = 0;      // Iterator for scanning words
    int characterindex = 0; // Iterator for scanning characters

    // Create parser for dividing string into keywords and storing them in an array.

    // While codetobeparsed[iterator] doesn't equal nullterminate character ('\0')
    for (iterator = 0; codetobeparsed[iterator] != '\0'; iterator++)
    {
        // Check for space bar, if we get space bar, store it in charpool.

        if (codetobeparsed[iterator] != '\0')
        {
            // If we get semicolon, store it in charpool.
            switch (codetobeparsed[iterator]) {
            case '(':
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                break;
            case ')':
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                break;
            case '{':
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                break;
            case '}':
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                break;
            case '[':
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                break;
            case ']':
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                break;
            case ';':
                // wordindex++;
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                break;
            case ',':
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                break;
            case '\n':
                // wordindex++;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                characterindex = 0;
                break;
            case '\t':
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                characterindex = 0;
                break;
            case ' ':
                characterindex = 0;
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                break;
            default:
                // If the previous checks did not complete, go to the next character in the array and set the key
                // just set the character as usual.
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                characterindex++;
                break;
            }

            // If the previous character was a special character, we're not dealing with a multichar word,
            // if we got a special character incoming, characterindex = 0 and deal with it!
            if (codetobeparsed[iterator+1] == '('
                || codetobeparsed[iterator+1] == ')'
                || codetobeparsed[iterator+1] == '{'
                || codetobeparsed[iterator+1] == '}'
                || codetobeparsed[iterator+1] == '['
                || codetobeparsed[iterator+1] == ']'
                || codetobeparsed[iterator+1] == ';'
                || codetobeparsed[iterator+1] == ','
                || codetobeparsed[iterator+1] == '\n'
                || codetobeparsed[iterator+1] == '\t'
                || codetobeparsed[iterator+1] == ' ')
            {  
                characterindex = 0;
                // wordindex++;
                // charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                // If the current character is special character AND the next one is one also.
                if (codetobeparsed[iterator] != ' '
                    && codetobeparsed[iterator] != '{'
                    && codetobeparsed[iterator] != '}'
                    && codetobeparsed[iterator] != ';'
                    && codetobeparsed[iterator] != '\n')
                {
                    wordindex++;
                }
            } else if (codetobeparsed[iterator+1] == ' ') {
                charPool.charpool[wordindex][characterindex] = codetobeparsed[iterator];
                wordindex++;
                // characterindex = 0;
            }
        }

    }

    return charPool;
}

pools::keywordpool lexobject(pools::charpool parsedobject) {

    // Lexer: categorize keywords and define them as types, identifiers, names, operators, values and special symbols.

    // Create object for variable pool
    pools::keywordpool keywordPool;

    // Create variables for iterating...
    int iterator = 0;        // Iterator for loops, counts the cycles
    int wordindex = 0;        // Word index iterator
    int worditerator = 0;        // Word index iterator #2 (fixed the whole program)
    int characterindex = 0;        // Character index iterator

    // Counter for words in charpool 
    int wordcounter = 0;

    // Count all words in charpool
    // For as long as charpool[iterator][0] != "\0", wordcounter++ and iterator++;
    for (int iterator = 0; parsedobject.charpool[iterator][0] != "\0"; iterator++) {
        wordcounter++;
    }

    // For all words in wordlist; do for loop with clause (parsedobject.charpool[wordindex][worditerator] != "\0")
    // and set the keys, as normal. then, when we get "\0"
    for (iterator = 0; iterator <= wordcounter; iterator++) {

        // Count the length of every word with characterindex, until ntchar2 found...
        // and set the keys, this sets the integer key perfectly, next we need to check for space...
        for (worditerator = 0; parsedobject.charpool[wordindex][worditerator] != "\0"; worditerator++) {
            keywordPool.keywordpool[wordindex][0] += parsedobject.charpool[wordindex][characterindex];
            characterindex++;
        }

        // To check for the space bar we need to increment wordindex by 1
        wordindex++;
        characterindex = 0;

        // If we get a space, wordindex++ and reset characterindex and go for the next word
        if (parsedobject.charpool[wordindex][characterindex] == " ") {
            // Here we can decide if we want to include spaces or not
            keywordPool.keywordpool[wordindex][0] = " "; // Comment out this line to not include spaces
            // Increment wordindex, for getting the next word since space is only 1-letter.
            wordindex++;
            // After setting the key, just reset characterindex for the next character.
            characterindex = 0;
        }
    }

    return keywordPool;
}

pools::compiledobject compile(pools::keywordpool lexedobject) {

    // Count the number of arrays/words in struct
    int wordindex = 0;   // Create variable for iterating through wordindexes

    // Define combiledobj object
    pools::compiledobject compiledobj;

    // For as long as keywordpool[wordindex][0] != dk_ntchar
    // check if data types found and convert them
    for (int iterator = 0; lexedobject.keywordpool[iterator][0] != "\0"; iterator++) {

        if (lexedobject.keywordpool[iterator][0] == "integer") {
            lexedobject.keywordpool[iterator][0] = "int";
        }

        if (lexedobject.keywordpool[iterator][0] == "decimal") {
            lexedobject.keywordpool[iterator][0] = "float";
        }
    }

    // combine the keywords into an compiledpool array
    for (int iterator = 0; lexedobject.keywordpool[iterator][0] != "\0"; iterator++) {
        compiledobj.compiledstring[0][0] += lexedobject.keywordpool[iterator][0];
    }

    // Return the compiled object
    return compiledobj;
}

int main(int argc, char* argv[]) {

    // Program variables
    std::string filename;

    // User input for filename
    std::cout << "Enter output file name with (.cpp): ";
    cin >> filename;

    // User message and input
    std::cout << "The Rustic C language is just c++ with minor changes." << "\n"  
        << "It goes as follows: " << "\n"
        << "int = integer, and float = decimal." << "\n"
        << "Rustic coding!" << "\n"
        << "----------------" << "\n"
        << "Write code on the line below this one..." << "\n" 
        << "Press CTRL+X on a new line to compile and write!" << "\n";

    std::string rusticcline;
    std::string linearray[1];
    int lineiterator;
    int linelimit = 128;
    int linecount;

    cin.clear();
    cin.seekg(0);

    for (int iterator = 0; rusticcline != "\x18"; iterator++) {
        
        if (rusticcline != "\x18") {
            if (iterator == linelimit-1) {
                linearray[0] += rusticcline;
            } else {
                std::cout << ": ";
                getline(cin, rusticcline);
                if (rusticcline == "\x18") {
                    std::cout << "Entered CTRL+X. Exiting..." << std::endl;
                } else {
                    if (rusticcline == "\x18") {
                        linearray[0] += rusticcline;
                        linecount++;
                    } else {
                        linearray[0] += rusticcline + "\n";
                    }
                }
            }
        }
    }

    // std::cout << linearray[0] << std::endl;

    // Pass the source to the parsestring function and return parsed object
    pools::charpool parsedobject = parsestring(linearray[0]);

    // Pass the parsed object
    pools::keywordpool lexedobject = lexobject(parsedobject);

    // Print compiling
    std::cout << "Compiling..." << std::endl;

    // Compiler
    pools::compiledobject compiledobj = compile(lexedobject);

    // Create file
    std::ofstream cppfile(filename.c_str());

    // Print writing to file
    std::cout << "Writing to:" << filename << std::endl;

    // Write to file
    cppfile << compiledobj.compiledstring[0][0];

    // Close the file
    cppfile.close();

    // Pause
    system("pause");

    // return the exit code and exit program 
    return 0;
}