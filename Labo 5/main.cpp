#include <iostream>
#include <string>
#include <list>
#include "Code/CloseWords.h"
#include "Code/Dictionary.h"

using namespace std;

int main()
{
	Dictionary d("Data/dictionary.txt", 0);
	std::cout << d.checkWord("hello") << std::endl;

	std::list<std::string> words = CloseWords::getCloseWords("salut");

	for (std::list<std::string>::iterator word = words.begin(); word != words.end(); word++) {
		std::cout << *word << std::endl;
	}

	return 0;
}
