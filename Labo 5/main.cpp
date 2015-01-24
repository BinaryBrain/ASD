#include <iostream>
#include <string>
#include <unordered_set>
#include "Code/CloseWords.h"
#include "Code/Dictionary.h"

using namespace std;

void checker(Dictionary *d, std::string toCheck) {
    if(!d->checkWord(toCheck)) {
        std::cout << "*" << toCheck << std::endl;
        // Hypothèse 1
        std::unordered_set<std::string> words1 = CloseWords::getCloseWordsToMany(toCheck);
        for(std::unordered_set<std::string>::iterator word = words1.begin(); word != words1.end(); word++) {
            if (d->checkWord(*word)) {
                std::cout << "1: " << *word << std::endl;
            }
        }

        // Hypothèse 2
        std::unordered_set<std::string> words2 = CloseWords::getCloseWordsMissing(toCheck);
        for(std::unordered_set<std::string>::iterator word = words2.begin(); word != words2.end(); word++) {
            if (d->checkWord(*word)) {
                std::cout << "2: " << *word << std::endl;
            }
        }

        // Hypothèse 3
        std::unordered_set<std::string> words3 = CloseWords::getCloseWordsWrong(toCheck);
        for(std::unordered_set<std::string>::iterator word = words3.begin(); word != words3.end(); word++) {
            if (d->checkWord(*word)) {
                std::cout << "3: " << *word << std::endl;
            }
        }

        // Hypothèse 4
        std::unordered_set<std::string> words4 = CloseWords::getCloseWordsSwap(toCheck);
        for(std::unordered_set<std::string>::iterator word = words4.begin(); word != words4.end(); word++) {
            if (d->checkWord(*word)) {
                std::cout << "4: " << *word << std::endl;
            }
        }
    }
}

int main() {
    std::string line;
    std::ifstream s("Data/input_multi.txt");

	Dictionary d("Data/dictionary.txt", 0);

    // Read the file line by line
    while (std::getline(s, line))
    {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz'";
        std::string buffer;

        // Lexer
        for(char c : line) {
            std::size_t found = alphabet.find_first_of(c);

            if (found == std::string::npos) {
                if (!buffer.empty()) {
                    // Check a word
                    checker(&d, buffer);
                    buffer = "";
                }
            } else {
                buffer.push_back(c);
            }
        }
    }

    s.close();
	return 0;
}
