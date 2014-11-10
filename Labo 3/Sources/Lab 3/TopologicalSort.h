//
//  TopologicalSort.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 08.10.14.
//
//  A implementer
//  Classe permettant le tri topologique d'un graphe oriente

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include <vector>
#include <stdlib.h>

namespace ASD2 {
    
    template < typename GraphType >
    class TopologicalSort {
    private:
        /* A DEFINIR */
        Graph* g;
        std::vector<int> postOrder;
    
    public:
        //constructeur
        TopologicalSort(const GraphType & g) {
            this->g = g;/*
            if(isDAG()) {
                // stuff?
            } else {
                // other stuff?
                std::cout << "there's a cycle and you suck";
            }*/
            /* A IMPLEMENTER */
            /* vous devez verifier la presence d'un cycle */
        }
        
        //indique si le graphe est DAG (Directed Acyclic Graph))
        bool IsDAG() {
            // if cycle, is not dag, blabliblou
            /* A IMPLEMENTER */
            //return ...
        }
        
        //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
        const std::vector<int>& Order() {
            DFS<Graph> P(g);
            P.visit(0, (int){}, [&](int w){
                postOrder.insert(0, w)
            });
            /* A IMPLEMENTER */
            //return ...
        }
    };
}
#endif
