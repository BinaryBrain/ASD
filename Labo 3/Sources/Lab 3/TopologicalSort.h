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

namespace ASD2 {
    
    template < typename GraphType >
    class TopologicalSort {
    private:
        /* A DEFINIR */
    
    public:
        //constructeur
        TopologicalSort(const GraphType & g) {
            /* A IMPLEMENTER */
            /* vous devez verifier la presence d'un cycle */
        }
        
        //indique si le graphe est DAG (Directed Acyclic Graph))
        bool IsDAG() {
            /* A IMPLEMENTER */
            //return ...
        }
        
        //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
        const std::vector<int>& Order() {
            /* A IMPLEMENTER */
            //return ...
        }
    };
}
#endif
