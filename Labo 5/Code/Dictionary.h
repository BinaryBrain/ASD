#ifndef Dictionary_h
#define Dictionary_h

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

class Dictionary
{
private:
	std::set<std::string> dictionary;

public:
	Dictionary(const std::string& filename, int mode)
	{
		std::string line;

		std::ifstream s(filename);
		while (std::getline(s, line))
		{
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);
			dictionary.insert(line);
		}
		s.close();
	}

	bool checkWord(const std::string& word)
	{
		return dictionary.find(word) != dictionary.end();
	}
};

#endif