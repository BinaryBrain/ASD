#include <iostream>
#include "Dictionary.h"

using namespace std;

int main()
{
	Dictionary d("Data/dictionary.txt", 0);
	std::cout << d.checkWord("hello") << std::endl;

	std::cout << "Hello world!" << std::endl;
	return 0;
}
