#include <iostream>
#include <string>
#include <unordered_set>
#include "Code/CloseWords.h"
#include "Code/Dictionary.h"

using namespace std;

int main()
{
	Dictionary d("Data/dictionary.txt", 0);
	std::cout << d.checkWord("hello") << std::endl;

    std::unordered_set<std::string> words = CloseWords::getCloseWords("salut");

    for(std::unordered_set<std::string>::iterator word = words.begin(); word != words.end(); word++) {
        std::cout << *word << std::endl;
    }

	return 0;
}
