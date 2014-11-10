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
        /* A DEFINIR */
        
    public:

        //constructeur
        DirectedCycle(const GraphType& g) {
            /* A IMPLEMENTER */
        }
        
        //indique la presence d'un cycle
        bool HasCycle() {
            /* A IMPLEMENTER */
            //return ...
        }
        
        //liste les indexes des sommets formant une boucle
        std::list<int> Cycle() {
            /* A IMPLEMENTER */
            //return ...
        }
        
    };
    
}

#endif
