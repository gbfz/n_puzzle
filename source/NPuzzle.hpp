#pragma once
#include "Node.hpp"
#include "IHeuristic.hpp"

namespace ft {

struct NPuzzle {
	Grid initial;
	Grid goal;
	const int side;
	std::unique_ptr<IHeuristic> heuristic;

	NPuzzle(const Grid& grid, std::unique_ptr<IHeuristic> heuristic);

	std::vector<Nodeptr> next_states(Nodeptr node) const;
	int h_score(Nodeptr node) const;
};

}
