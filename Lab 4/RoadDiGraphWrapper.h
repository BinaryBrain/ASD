#ifndef ROADDIGRAPHWRAPPER_H
#define ROADDIGRAPHWRAPPER_H

// Wrapper destin� � cr�er un graph de routes
class RoadDiGraphWrapper {
private:
	RoadNetwork& rn;

    std::function<double(int, double)> weightFunc = [](int l, double m) {
        return l;
    };

public:
    
	typedef ASD2::WeightedDirectedEdge<double> Edge;
	RoadDiGraphWrapper(RoadNetwork& rn2): rn(rn2) {}

    template<typename Func>
	void setWeightFunc(Func f) {
        this->weightFunc = f;
	}

	int V() const {
		return rn.cities.size();
	}

	template<typename Func>
	void forEachAdjacentEdge(int v, Func func) const {
		std::vector<int> edges = rn.cities.at(v).roads;

        for (std::vector<int>::iterator edge = edges.begin(); edge != edges.end(); edge++) {
			std::pair<int, int> p = rn.roads.at(*edge).cities;
			int w = (p.first != v) ? p.first : p.second;
			int weight = weightFunc(rn.roads.at(*edge).lenght, rn.roads.at(*edge).motorway.Value());

			func(ASD2::WeightedDirectedEdge<double>(v, w, weight));
		}
	}
        
       
};

#endif // ROADDIGRAPHWRAPPER_H
