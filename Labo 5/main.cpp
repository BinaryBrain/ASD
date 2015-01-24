#include <iostream>
#include <string>
#include <unordered_set>
#include "Code/CloseWords.h"
#include "Code/Dictionary.h"

using namespace std;

int main()
{
	Dictionary d("Data/dictionary.txt", 0);

    std::string toCheck = "civilized";

    std::unordered_set<std::string> words1 = CloseWords::getCloseWordsToMany(toCheck);
    std::unordered_set<std::string> words2 = CloseWords::getCloseWordsMissing(toCheck);
    std::unordered_set<std::string> words3 = CloseWords::getCloseWordsWrong(toCheck);
    std::unordered_set<std::string> words4 = CloseWords::getCloseWordsSwap(toCheck);

    int i = 0;

    // Hypothèse 1
    for(std::unordered_set<std::string>::iterator word = words1.begin(); word != words1.end(); word++) {
        if (d.checkWord(*word)) {
            std::cout << "1: " << *word << std::endl;
        }
    }

    // Hypothèse 2
    for(std::unordered_set<std::string>::iterator word = words2.begin(); word != words2.end(); word++) {
        if (d.checkWord(*word)) {
            std::cout << "2: " << *word << std::endl;
        }
    }

    // Hypothèse 3
    for(std::unordered_set<std::string>::iterator word = words3.begin(); word != words3.end(); word++) {
        if (d.checkWord(*word)) {
            std::cout << "3: " << *word << std::endl;
        }
    }

    // Hypothèse 4
    for(std::unordered_set<std::string>::iterator word = words4.begin(); word != words4.end(); word++) {
        if (d.checkWord(*word)) {
            std::cout << "4: " << *word << std::endl;
        }
    }

	return 0;
}
