//
//  DirectedCycle.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 08.10.14.
//
//  A implementer
//  Classe permettant la detection de cycle sur un graphe oriente

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <map>

namespace ASD2 {
    template<typename GraphType>
    class DirectedCycle {
    private:
        const GraphType& g;
        bool hasCycle;
        std::vector<bool> onStack;
        std::vector<bool> marked;
        std::vector<int> precycle;
        std::list<int> cycle;
        int cycleVertex;

        void dfs(int v) {
            onStack[v] = true;
            marked[v] = true;

            for (int w: g.adjacent(v)) {
                if (!marked[w]) {
                    precycle.push_back(v);
                    dfs(w);
                } else if (onStack[w]) {
                    cycleVertex = w;
                    hasCycle = true;
                }

                if (hasCycle) {
                    return;
                }

                precycle.clear();
            }

            onStack[v] = false;
        }

        void processCycle() {
            for (std::vector<int>::reverse_iterator it = precycle.rbegin(); it != precycle.rend(); ++it) {
                cycle.push_front(*it);

                if (*it == cycleVertex) {
                    return;
                }
            }
        }

    public:
        void printCycle() {
            std::cout << "Cycle is: ";
            for (std::list<int>::iterator it = cycle.begin(); it != cycle.end(); ++it) {
                std::cout << g.name(*it) << " -> ";
            }

            std::cout << g.name(cycleVertex) << std::endl;
        }

        // constructor
        DirectedCycle(const GraphType& G): g(G) {
            onStack.assign(G.V(), false);
            marked.assign(G.V(), false);
            hasCycle = false;

            dfs(0);
            processCycle();
        }

        //indique la presence d'un cycle
        bool HasCycle() {
            return hasCycle;
        }

        //liste les indexes des sommets formant une boucle
        std::list<int> Cycle() {
            return cycle;
        }
    };
}

#endif
