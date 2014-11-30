//
//  main.cpp
//  Labo 3
//
//  Created by Olivier Cuisenaire on 03.11.14.
//

#include <iostream>
#include <stdlib.h>
#include "DiGraph.h"
#include "TopologicalSort.h"

// vous devez reutiliser celui du labo 2, ex 3 (cf. donnee)
#include "SymbolGraph.h"

using namespace ASD2;
using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);

    bool ok = true;

    std::string line;

    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        auto names = ASD2::split(line,delim);

        for(size_t i = 1; i < names.size(); ++i) {
            int v = SG.index(names[0]); // cours
            int w = SG.index(names[i]); // ieme prerequis

            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            }
        }
    }
    s.close();

    return ok;
}

int main(int argc, const char * argv[]) {
    SymbolGraph<DiGraph> sg1("prerequis.txt", ',');
    SymbolGraph<DiGraph> sg2("prerequis2.txt", ',');

    TopologicalSort<SymbolGraph<DiGraph>> ts1(sg1);
    TopologicalSort<SymbolGraph<DiGraph>> ts2(sg2);

    ts1.Order();
    ts2.Order();

    return EXIT_SUCCESS;
}
