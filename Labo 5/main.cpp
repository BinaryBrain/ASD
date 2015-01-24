#include <iostream>
#include <string>
#include <list>
#include "Code/CloseWords.h"

int main()
{
    std::cout << "Hello world!" << std::endl;
    std::list<std::string> words = CloseWords::getCloseWords("salut");

    for(std::list<std::string>::iterator word = words.begin(); word != words.end(); word++) {
        std::cout << *word << std::endl;
    }

    return 0;
}
