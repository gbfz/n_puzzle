#pragma once
#include "Grid.hpp"
#include <iostream>
#include <memory>
#include <algorithm>
#include <ranges>
#include <tuple>
#include <functional>

#include "SnailFill.hpp"

namespace ft {

struct NPuzzle {
	Grid initial;
	Grid goal;
	const int side;

	NPuzzle(Grid&& grid);
	NPuzzle(const Grid& grid);

	auto get_next_states(Grid& g) -> std::vector<Grid>;

};

}
