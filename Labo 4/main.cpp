//
//  main.cpp
//  Labo4
//
//  Created by Olivier Cuisenaire on 18.11.14.
//
//

#include <iostream>
#include <ctime>

#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDiGraph.h"
#include "RoadNetwork.h"
#include "MinimumSpanningTree.h"
#include "ShortestPath.h"
#include "RoadDiGraphWrapper.h"
#include "RoadGraphWrapper.h"

using namespace std;

// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau routier rn. Le critere a optimiser est la distance.

void PlusCourtChemin(const string& depart, const string& arrivee, RoadNetwork& rn) {
    int u = rn.cityIdx.at(depart);
    int v = rn.cityIdx.at(arrivee);

    RoadDiGraphWrapper rdgw(rn);
    rdgw.setWeightFunc([](int l, double m){
        return l;
    });

    ASD2::DijkstraSP<RoadDiGraphWrapper> sp(rdgw, u);

    std::vector<ASD2::WeightedDirectedEdge<double>> edges = sp.PathTo(v);

    double totalLength = 0;

    for (std::vector<ASD2::WeightedDirectedEdge<double>>::iterator edge = edges.begin(); edge != edges.end(); edge++) {
        std::string from = rn.cities.at(edge->From()).name;
        std::string to = rn.cities.at(edge->To()).name;
        double len = edge->Weight();

        totalLength += len;

        std::cout << "De " << from << " à " << to << ": " << len << "km." << std::endl;

    }

    std::cout << "Distance totale: " << totalLength << "km." << std::endl << std::endl;
}

// Calcule et affiche le plus rapide chemin de la ville depart a la ville arrivee via la ville "via"
// en passant par le reseau routier rn. Le critere a optimiser est le temps de parcours
// sachant que l'on roule a 120km/h sur autoroute et 70km/h sur route normale.

void PlusRapideChemin(const string& depart, const string& arrivee, const string& via, RoadNetwork& rn) {
    int u = rn.cityIdx.at(via);
    int v = rn.cityIdx.at(depart);
    int w = rn.cityIdx.at(arrivee);

    RoadDiGraphWrapper rdgw(rn);
    rdgw.setWeightFunc([](int l, double m){
        return (l * m / 120.0)*60.0 + (l * (1 - m) / 70.0)*60.0;
    });

    ASD2::DijkstraSP<RoadDiGraphWrapper> sp(rdgw, u);

    std::vector<ASD2::WeightedDirectedEdge<double>> edges1 = sp.PathTo(v);
    std::vector<ASD2::WeightedDirectedEdge<double>> edges2 = sp.PathTo(w);

    double totalLength = 0;

    // Inversion du chemin
    std::reverse(edges1.begin(), edges1.end());
    for (std::vector<ASD2::WeightedDirectedEdge<double>>::iterator edge = edges1.begin(); edge != edges1.end(); edge++) {
        std::string from = rn.cities.at(edge->To()).name;
        std::string to = rn.cities.at(edge->From()).name;

        double len = edge->Weight();
        totalLength += len;

        std::cout << "De " << from << " à " << to << ": " << len << " minutes." << std::endl;
    }

    for (std::vector<ASD2::WeightedDirectedEdge<double>>::iterator edge = edges2.begin(); edge != edges2.end(); edge++) {
        std::string from = rn.cities.at(edge->From()).name;
        std::string to = rn.cities.at(edge->To()).name;

        double len = edge->Weight();
        totalLength += len;

        std::cout << "De " << from << " à " << to << ": " << len << " minutes." << std::endl;
    }

    std::cout << "Temps total: " << totalLength << " minutes." << std::endl << std::endl;
}

// Calcule et affiche le plus reseau a renover couvrant toutes les villes le moins
// cher, en sachant que renover 1km d'autoroute coute 15 MF, et renover 1km de route normale
// coute 7 MF.


void ReseauLeMoinsCher(RoadNetwork &rn) {
    
    
    RoadGraphWrapper rgw(rn);
    rgw.setWeightFunc([](int len, double frac){
        return (frac * len * 15) + ((1-frac) * len * 7);
    });
    
    auto mst = ASD2::MinimumSpanningTree<RoadGraphWrapper>::Kruskal(rgw);
    
    double cost = 0;
    for(auto m: mst){
               
        int v = m.Either();
        int w = m.Other(v);
        int T = m.Weight();
        std::string from = rn.cities.at(v).name;
        std::string to = rn.cities.at(w).name;
        
        cout << "De " << from << " à " << to << " : " << T << " MF." << endl;
        cost += m.Weight();
    }
    cout << "Cout des travaux: " << cost << " MF." << endl;
    
}

// compare les algorithmes Dijkstra et BellmanFord pour calculer les plus courts chemins au
// sommet 0 dans le graphe defini par filename.

void testShortestPath(string filename)
{
    cout << "Testing " << filename << endl;

    bool ok = true;

    typedef ASD2::EdgeWeightedDiGraph<double> Graph;
    Graph ewd(filename);

    clock_t startTime = clock();

    ASD2::BellmanFordQueueSP<Graph> referenceSP(ewd,0);

    cout << "Bellman-Ford: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    startTime = clock();

    ASD2::DijkstraSP<Graph> testSP(ewd,0);

    cout << "Dijkstra:     " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;


    for (int v=0; v<ewd.V(); ++v) {
        if (referenceSP.DistanceTo(v) != testSP.DistanceTo(v) ) {
            cout << "Oops: vertex" << v << " has " << referenceSP.DistanceTo(v) << " != " <<  testSP.DistanceTo(v) << endl;
            ok = false;
            break;
        }
    }

    if(ok) cout << " ... test succeeded " << endl << endl;
}

int main(int argc, const char * argv[]) {

    testShortestPath("tinyEWD.txt");
    testShortestPath("mediumEWD.txt");
    testShortestPath("1000EWD.txt");
    testShortestPath("10000EWD.txt");
    //testShortestPath("largeEWD.txt"); // disponible sur dossier du cours

    RoadNetwork rn("reseau.txt");

    cout << "1. Chemin le plus court entre Genève et Emmen:" << endl;

    PlusCourtChemin("Geneve", "Emmen", rn);

    cout << "2. Chemin le plus court entre Lausanne et Bâle:" << endl;

    PlusCourtChemin("Lausanne", "Basel", rn);

    cout << "3. Chemin le plus rapide entre Genève et Emmen en passant par Yverdon:" << endl;

    PlusRapideChemin("Geneve", "Emmen", "Yverdon-Les-Bains", rn);

    cout << "4. Chemin le plus rapide entre Genève et Emmen en passant par Vevey:" << endl;

    PlusRapideChemin("Geneve", "Emmen", "Vevey", rn);

    cout << "5. Quelles routes doivent être renovées? Quel sera le coût de la rénovation de ces routes?" << endl;

    ReseauLeMoinsCher(rn);

    return 0;
}
