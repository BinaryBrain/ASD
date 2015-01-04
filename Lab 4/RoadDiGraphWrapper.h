#ifndef ROADDIGRAPHWRAPPER_H
#define ROADDIGRAPHWRAPPER_H

class RoadDiGraphWrapper {
private:
	RoadNetwork rn;

public:
	typedef ASD2::WeightedDirectedEdge<double> Edge;
	RoadDiGraphWrapper(const RoadNetwork rn2): rn(rn2) {}

	int V() const {
		return rn.cities.size();
	}

	template<typename Func>
	void forEachAdjacentEdge(int v, Func func) const {
		std::vector<int> edges = rn.cities.at(v).roads;

        for (std::vector<int>::iterator edge = edges.begin(); edge != edges.end(); edge++) {
			std::pair<int, int> p = rn.roads.at(*edge).cities;
			int w = (p.first != v) ? p.first : p.second;
			int l = rn.roads.at(*edge).lenght;

			func(ASD2::WeightedDirectedEdge<double>(v, w, l));
		}
	}
};

#endif // ROADDIGRAPHWRAPPER_H
