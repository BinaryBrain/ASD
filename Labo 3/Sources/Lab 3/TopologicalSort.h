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
#include "ParcoursEnProfondeur.h"
#include "SymbolGraph.h"
#include <vector>
#include <stdlib.h>

namespace ASD2 {
    template < typename GraphType >
    class TopologicalSort {
    private:
        DirectedCycle<GraphType> dc;
        std::vector<int> reversePostOrder;

    public:
        //constructeur
        TopologicalSort(const GraphType & g): dc(g) {
            if(IsDAG()) {
                g.V();
                reversePostOrder.resize(g.V());
                int length = g.V() - 1;
                DFS<GraphType> dfs(g);

                dfs.visit(0, [](int){}, [&](int v) {
                    reversePostOrder[length--] = v;
                });
            } else {
                std::cout << "there's a cycle.";
                exit(1);
            }
        }

        //indique si le graphe est DAG (Directed Acyclic Graph))
        bool IsDAG() {
            return !dc.HasCycle();
        }

        //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
        const std::vector<int>& Order() {
            /* DFS<Graph> P(g);
            P.visit(0, (int){}, [&](int w){
                postOrder.insert(0, w)
            });
            */
            /* A IMPLEMENTER */
            //return ...
        }
    };
}
#endif
