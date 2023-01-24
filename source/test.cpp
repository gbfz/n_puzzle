#include "NPuzzle.hpp"
#include "ManhattanDistance.hpp"

#include <limits>
#include <list>
#include <queue>
#include <optional>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <string>
#include <tuple>
#include <unordered_map>

using namespace ft;

struct compare_f_score {
	bool operator()(const Nodeptr& lhs, const Nodeptr& rhs) const {
		return lhs->f_score > rhs->f_score;
	}
};

namespace ft {
	using node_queue = std::priority_queue<Nodeptr, std::vector<Nodeptr>, compare_f_score>;
}

std::optional<Nodeptr> AStar(NPuzzle& puzzle, size_t& open_max, size_t& memory_max, size_t& steps)
{
	ft::node_queue frontier;
	std::unordered_set<Nodeptr> closed_set;

	auto init = ft::make_node(puzzle.initial, 0, 0, nullptr);
	init->f_score = puzzle.h_score(init);
	frontier.emplace(std::move(init));

	while (!frontier.empty())
	{
		open_max = std::max(open_max, frontier.size());
		memory_max = std::max(memory_max, frontier.size() + closed_set.size());
		steps += 1;

		auto state = frontier.top();
		if (state->grid == puzzle.goal)
			return state;
		frontier.pop();
		for (auto next : puzzle.next_states(state)) {
			auto new_cost = state->g_score + 1;
			if (!closed_set.contains(next) || new_cost < next->g_score) {
				next->f_score = new_cost + puzzle.h_score(next);
				frontier.emplace(next);
			}
		}
	}
	return {};
}

std::pair<std::optional<Nodeptr>, int> dfs_contour(Nodeptr node, int f_limit, const NPuzzle& puzzle, size_t& steps)
{
	steps += 1;
	if (node->grid == puzzle.goal)
		return {node, f_limit};
	if (node->f_score > f_limit)
		return {{}, node->f_score};
	auto next_f = std::numeric_limits<int>::max();
	for (auto next : puzzle.next_states(node)) {
		auto [result, new_f] = dfs_contour(next, f_limit, puzzle, steps);
		if (result)
			return {result, f_limit};
		next_f = std::min(next_f, new_f);
	}
	return {{}, next_f};
}

Nodeptr IDAStar(NPuzzle& puzzle, size_t& steps)
{
	auto node = ft::make_node(puzzle.initial, 0, 0, nullptr);
	node->f_score = puzzle.h_score(node);
	int f_limit = node->f_score;
	std::optional<Nodeptr> out;
	while (!out) {
		std::tie(out, f_limit) = dfs_contour(node, f_limit, puzzle, steps);
	}
	return out.value();
}

std::vector<Grid> trace_path(Nodeptr goal)
{
	std::vector<Grid> path;
	while (goal != nullptr) {
		path.emplace_back(goal->grid);
		goal = goal->parent;
	}
	return {path.rbegin(), path.rend()};
}

int main(int ac, char** av) {
	auto g1 = Grid {
		{{0, 0}, 0},
		{{1, 0}, 2},
		{{2, 0}, 3},

		{{0, 1}, 1},
		{{1, 1}, 4},
		{{2, 1}, 5},

		{{0, 2}, 8},
		{{1, 2}, 7},
		{{2, 2}, 6},
	};
	auto g2 = Grid {
		{{0, 0}, 1},
		{{1, 0}, 14},
		{{2, 0}, 2},
		{{3, 0}, 11},

		{{0, 1}, 8},
		{{1, 1}, 6},
		{{2, 1}, 12},
		{{3, 1}, 13},

		{{0, 2}, 10},
		{{1, 2}, 0},
		{{2, 2}, 4},
		{{3, 2}, 15},

		{{0, 3}, 7},
		{{1, 3}, 3},
		{{2, 3}, 9},
		{{3, 3}, 5},
	};
	auto g3 = Grid {
		{{0, 0}, 3},
		{{1, 0}, 2},
		{{2, 0}, 1},

		{{0, 1}, 8},
		{{1, 1}, 0},
		{{2, 1}, 7},

		{{0, 2}, 6},
		{{1, 2}, 5},
		{{2, 2}, 4},
	};

	NPuzzle np(g3, std::make_unique<ManhattanDistance>());

	if (ac == 2 && std::string(av[1]) == "a")
	{ // A*
		size_t open_max = 0;
		size_t memory_max = 0;
		size_t steps = 0;
		auto node = AStar(np, open_max, memory_max, steps).value();
		auto path = trace_path(node);
		std::cout << "Max size of open set: " << open_max << '\n';
		std::cout << "Max memory usage:     " << memory_max << '\n';
		std::cout << "Steps taken:          " << steps << '\n';
		std::cout << "Path length:          " << path.size() << "\n\n";

		for (const auto& grid : path) {
			grid.print();
		}
	}

	else if (ac == 2 && std::string(av[1]) == "i")
	{ // IDA*
		size_t steps = 0;
		auto node = IDAStar(np, steps);
		auto path = trace_path(node);
		std::cout << "Steps taken:          " << steps << "\n\n";

		for (const auto& grid : path) {
			grid.print();
		}
	}
}
