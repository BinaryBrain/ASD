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

namespace ASD2 {
    template<typename GraphType>
    class DirectedCycle {
    private:
        const GraphType& g;
        bool hasCycle;
        std::vector<bool> onStack;
        std::vector<bool> marked;

    public:
        // constructor
        DirectedCycle(const GraphType& g) {
            dfs(0);
        }

        void dfs(int v) {
            onStack[v] = true;

            for (int w: g.adjacent(v)) {
                if (hasCycle) {
                    return;
                }

                if (!marked[w]) {
                    dfs(w);
                } else if (onStack[w]) {
                    hasCycle = true;
                }
            }

            onStack[v] = false;
        }

        //indique la presence d'un cycle
        bool HasCycle() {
            return hasCycle;
        }

        //liste les indexes des sommets formant une boucle
        std::list<int> Cycle() {
            /* A IMPLEMENTER */
            //return ...
        }

    };

}

#endif
