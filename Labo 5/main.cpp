// Léonard Berney, Sacha Bron

/*
 * Le choix de la structure de donnée STL s'est porté sur std::set. Cette structure présente l'avantage
 * d'être un arbre binaire équilibré et ordonné, ce qui rend la recherche particulièrement rapide sans
 * que l'insertion soit beaucoup plus lente que dans une autre structure.
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include "Code/CloseWords.h"
#include "Code/Dictionary.h"
#include <time.h>

void checker(Dictionary *d, std::string toCheck, std::ofstream *output) {
	if (!d->checkWord(toCheck)) {
		*output << "*" << toCheck << std::endl;
		// Hypothèse 1
		std::unordered_set<std::string> words1 = CloseWords::getToMany(toCheck);
		for (std::unordered_set<std::string>::iterator word = words1.begin(); word != words1.end(); word++) {
			if (d->checkWord(*word)) {
				*output << "1: " << *word << std::endl;
			}
		}

		// Hypothèse 2
		std::unordered_set<std::string> words2 = CloseWords::getMissing(toCheck);
		for (std::unordered_set<std::string>::iterator word = words2.begin(); word != words2.end(); word++) {
			if (d->checkWord(*word)) {
				*output << "2: " << *word << std::endl;
			}
		}

		// Hypothèse 3
		std::unordered_set<std::string> words3 = CloseWords::getWrong(toCheck);
		for (std::unordered_set<std::string>::iterator word = words3.begin(); word != words3.end(); word++) {
			if (d->checkWord(*word)) {
				*output << "3: " << *word << std::endl;
			}
		}

		// Hypothèse 4
		std::unordered_set<std::string> words4 = CloseWords::getSwap(toCheck);
		for (std::unordered_set<std::string>::iterator word = words4.begin(); word != words4.end(); word++) {
			if (d->checkWord(*word)) {
				*output << "4: " << *word << std::endl;
			}
		}
	}
}

int main() {
	clock_t tick;
	std::string line;
	std::ifstream input("Data/input_sh.txt");
	std::ofstream output("Data/output.txt");
	
	bool useSTD = 0; // 0 pour utiliser un tst 1 pour utiliser une structure stl

	std::cout << "Lecture du dictionaire..." << std::endl;
	tick = clock();
	Dictionary d("Data/dictionary.txt", useSTD);
	std::cout << "Temps de lecture: " << ((double)clock() - tick) / CLOCKS_PER_SEC << " sec." << std::endl;

	std::cout << "Lecture et correction du texte..." << std::endl;
	tick = clock();
	// Read the file line by line
	while (std::getline(input, line))
	{
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
		std::string buffer;

		// Lexer
		for (int i = 0; i < line.size(); i++)
		{
			char c = line.at(i);
			std::size_t found = alphabet.find_first_of(c);

			// Letter of the alphabet
			if (found != std::string::npos)
			{
				buffer.push_back(c);
			}
			// Single quote
			else if (c == '\'')
			{
				// Not first char of word
				if (!buffer.empty())
				{
					// Not last char of word
					if (i < line.size()-1 && alphabet.find_first_of(line.at(i+1)) != std::string::npos)
					{
						buffer.push_back(c);
					}
				}
			}
			// Other char
			else
			{
				if (!buffer.empty())
				{
					// Check a word
					checker(&d, buffer, &output);
					buffer = "";
				}
			}
		}
	}

	std::cout << "Temps de correction: " << ((double)clock() - tick) / CLOCKS_PER_SEC << " sec." << std::endl;

	input.close();
	output.close();
	return 0;
}
