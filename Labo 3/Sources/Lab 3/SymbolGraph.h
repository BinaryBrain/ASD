/*
 * File:   SymbolGraph.h
 * Author: Eléonore d'Agostino
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_H
#define	SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <unordered_map>

#include "Util.h"
#include "GraphUsingAdjacencyLists.h"

namespace ASD2
{
    template<typename GraphType>
    class SymbolGraph
    {
        typedef GraphType Graph;
    private:
        Graph* g;
        std::unordered_map<std::string,int> uMap;
        std::vector<std::string> uVector;

    public:

        ~SymbolGraph()
        {
            delete g;
        }

        //creation du SymbolGraph a partir du fichier movies.txt
        SymbolGraph(const std::string& filename, char separator) {
            //lecture du fichier, ligne par ligne puis element par element (separe par des /)
            std::string line;
            int cnt=0;
            std::vector<std::tuple<int,int>> tempEdges;

            std::ifstream s(filename);

            while (std::getline(s, line))
            {
                auto names = ASD2::split(line,separator);
                for( auto name : names ){
                    std::cout << name << " "; //on affiche le contenu du fichier,

                    // if name isn't in map, add it and increment
                    if(!uMap.count(name)){
                        uMap.insert({name,cnt});
                        uVector.push_back(name);
                        cnt++;
                    }

                    // if actor, add edge with movie
                    if(name != names[0]) {
                        tempEdges.push_back(std::make_tuple(uMap[names.at(0)], uMap[name]));
                    }
                }

                std::cout << std::endl;
            }
            s.close();

            g = new DiGraph(cnt);

            for(auto t : tempEdges) {
                g->addEdge(std::get<0>(t), std::get<1>(t));
            }
        }

        //verifie la presence d'un symbole
        bool contains(const std::string& name) const {
            return uMap.count(name);
        }

        //index du sommet correspondant au symbole
        int index(const std::string& name) const {
            // throws exception if wrong
            return uMap.at(name);
        }

        //symbole correspondant au sommet
        std::string name(int idx) const {
            return uVector.at(idx);
        }

        //symboles adjacents a un symbole
        std::vector<std::string> adjacent(const std::string & name) const {
            return g->adjacent(uMap.at(name));
        }

        const Graph& G() {
            return *g;
        }

    };

}

#endif	/* SYMBOLGRAPH_H */
