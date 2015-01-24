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
    // 1st file
    std::string f1 = "prerequis.txt";
    std::string f2 = "prerequis2.txt";

    SymbolGraph<DiGraph> sg1(f1, ',');
    TopologicalSort<SymbolGraph<DiGraph>> ts1(sg1);

    if (ts1.IsDAG()) {
        std::cout << f1 << " est un DAG." << std::endl;
        std::vector<int> order1 = ts1.Order();
        std::cout << "Order: ";
        for (int i: ts1.Order()) {
            std::cout << i << ",";
        }
        std::cout << endl;
        checkOrder(order1, sg1, f1, ',');
    } else {
        ts1.printCycle();
        std::cout << f1 << " n'est pas un DAG." << std::endl;
    }
    std::cout << endl;

    // 2nd file
    SymbolGraph<DiGraph> sg2(f2, ',');
    TopologicalSort<SymbolGraph<DiGraph>> ts2(sg2);

    if (ts2.IsDAG()) {
        std::cout << f2 << " est un DAG." << std::endl;
        std::vector<int> order2 = ts2.Order();
        cout << "Order: ";
        for (int i: ts1.Order()) {
            cout << i << ",";
        }
        std::cout << endl;
        checkOrder(order2, sg2, f2, ',');
    } else {
        std::cout << f2 << " n'est pas un DAG." << std::endl;
        ts2.printCycle();
    }
    std::cout << endl;

    return EXIT_SUCCESS;
}
