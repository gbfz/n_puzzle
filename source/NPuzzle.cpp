#include "NPuzzle.hpp"
#include "SnailFill.hpp"

namespace ft {

NPuzzle::NPuzzle(const Grid& grid, std::unique_ptr<IHeuristic> heuristic)
	: initial(grid)
	, goal(SnailFill{}.get_goal_state(initial))
	, side(grid.side)
	, heuristic(std::move(heuristic)) { }

std::vector<Nodeptr> NPuzzle::next_states(Nodeptr node) const
{
	std::vector<Nodeptr> states;
	for (auto tile : node->grid.neighbors_of_empty())
	{
		Grid next = node->grid;
		next.swap_empty_with(tile->second);
		auto new_state = make_node(
				std::move(next),
				node->g_score + 1,
				node->g_score + 1 + heuristic->h_score(next, goal),
				node);
		states.emplace_back(std::move(new_state));
	}
	return states;
}

int NPuzzle::h_score(Nodeptr node) const
{
	return heuristic->h_score(node->grid, goal);
}

}
