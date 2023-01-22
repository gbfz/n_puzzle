#include "NPuzzle.hpp"
#include <utility>

namespace ft {

NPuzzle::NPuzzle(const Grid& g)
	: initial(g)
	, side(initial.side) {
		goal.side = side;
}

NPuzzle::NPuzzle(Grid&& g)
	: initial(std::forward<Grid>(g))
	, side(initial.side) {
		goal.side = side;
}

auto NPuzzle::get_next_states(Grid& g) -> std::vector<Grid> {
	std::vector<Grid> next_states;
	for (auto neighbor : g.get_neighbors_of_empty()) {
		auto next = Grid(g);
		std::iter_swap(next.find(0), next.find(neighbor->second));
		next_states.emplace_back(std::move(next));
	}
	return next_states;
}

}
