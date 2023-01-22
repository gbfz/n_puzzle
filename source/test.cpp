#include "Grid.hpp"
#include <bits/ranges_algobase.h>
#include <iostream>
#include "NPuzzle.hpp"
#include "SnailFill.hpp"
#include <unistd.h>

auto println() { std::cout << '\n'; }

// 1 2 3
// 8   4
// 7 6 5

using namespace ft;

Grid test(NPuzzle& np, Grid& g) {
	for (auto& state : np.get_next_states(g)) {
		if (std::ranges::equal(state, np.goal))
			return state;
		state.print();
		sleep(1);
		test(np, state);
	}
	std::exit(42);
}

int main() {
	using namespace ft;
	auto grid = Grid {
		{ {0, 0}, 0},
		{ {1, 0}, 2},
		{ {2, 0}, 3},

		{ {0, 1}, 8},
		{ {1, 1}, 1},
		{ {2, 1}, 4},

		{ {0, 2}, 7},
		{ {1, 2}, 6},
		{ {2, 2}, 5},
	};
	/*
	grid.print();
	println();

	auto empty = grid.find({0, 0});
	auto right = grid.get_neighbor(empty->first, Change::Right);
	std::iter_swap(empty, right);
	grid.print();
	*/

	NPuzzle np(std::move(grid));
	np.initial.print();
	np.goal = SnailFill().get_goal_state(np.initial);
	println();
	println();

	test(np, np.initial);

	/*
	auto what = np.get_next_states(np.initial);
	for (auto&& s : what) {
		s.print();
		println();
	}
	*/
}
