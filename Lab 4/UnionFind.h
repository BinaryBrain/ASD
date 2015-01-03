//
//  UnionFind.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 27.10.14.
//

#ifndef ASD2_UnionFind_h
#define ASD2_UnionFind_h

#include <vector>

namespace ASD2
{
    //  Cette classe met en oeuvre de la structure Union-Find, aussi connue
    //  sous le nom de disjoint sets. Utilisé par l'algorithme de
    //  Kruskal.
    
    class UnionFind
    {
    private:
        // id[i] stocke l'id du parent de i dans l'arbre des classes d'équivalence
        std::vector<int> id;
        
        // sz[i] stocke la taille de l'arbre dont i est la racine.
        std::vector<int> sz;
        
    public:
        
        // Constructeur: spécifie le nombre N d'éléments
        UnionFind(int N);
        
        // Find renvoie l'id représentatif de la classe d'équivalence de p.
        int Find(int p) ;
        
        // Connected indique que p et q appartiennent à la même classe d'équivalence
        bool Connected(int p, int q);
        
        // Union fusionne les classes d'équivalence de p et q
        void Union(int p, int q);
    };
}

#endif
