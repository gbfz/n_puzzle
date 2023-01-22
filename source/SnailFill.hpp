#pragma once
#include "Grid.hpp"
#include <algorithm>

namespace ft {

struct SnailFill {

	Change dir = Change::Right;
	ft::coords center;
	int min_x = 0;
	int min_y = 0;
	int max_x = 0;
	int max_y = 0;

	auto get_puzzle_values(const Grid& g) -> std::vector<int>;
	auto next(ft::coords tile) -> ft::coords;
	auto get_goal_state(const Grid& g) -> Grid;
	auto init_coords(const int side) -> void;
};

}
