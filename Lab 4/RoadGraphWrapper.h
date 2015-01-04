/* 
 * File:   RoadGraphWrapper.h
 * Author: paulnta
 *
 * Created on 4. janvier 2015, 20:21
 */

#ifndef ROADGRAPHWRAPPER_H
#define	ROADGRAPHWRAPPER_H

#include "EdgeWeightedGraph.h"
#include "RoadNetwork.h"


class RoadGraphWrapper {
private:
    RoadNetwork rn;
        
    // Stock la fonction de coût avec valeur par défaut si non spécifiée
    std::function<double(int, double)> weightFunc = [](int l, double m) {
         return l;
    };

        
public:
    
	typedef ASD2::WeightedEdge<double> Edge;
	RoadGraphWrapper(const RoadNetwork rn2): rn(rn2){}

	int V() const {
		return rn.cities.size();
	}

        // Parcours toutes les routes
	template<typename Func>
	void forEachEdge(Func func) const {

            for(auto r : rn.roads ){

                int v = r.cities.first; 
                int w = r.cities.second;
                               
                // Calcule de poids avec la fonction de coût
                int weight =  weightFunc(r.lenght, r.motorway.Value());
                
                // applique la fonction sur un nouveau WeightedEdge
                func(ASD2::WeightedEdge<double>(v,w,weight)); 
            }
            
    
	}
        
        // Définie la fonction de coût
        void setWeightFunc (std::function<double(int, double)> weightFunc){
            this->weightFunc = weightFunc;
        }
        
       
};

#endif	/* ROADGRAPHWRAPPER_H */

