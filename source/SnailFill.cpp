#include "SnailFill.hpp"

namespace ft {

std::vector<int> SnailFill::get_puzzle_values(const Grid& g) {
	std::vector<int> values;
	for (auto [_, value] : g.grid)
		values.push_back(value);
	std::ranges::sort(values);
	std::ranges::rotate(values, std::next(values.begin()));
	return values;
}

ft::coords SnailFill::next(ft::coords tile) {
	using enum Change;
	if (tile == center)
		return tile;
	switch (dir) {
		case Right: if (tile.x < max_x)
						return {tile.x + 1, tile.y};
					dir = Change::Down;
					max_x -= 1;
		case Down:  if (tile.y < max_y)
						return {tile.x, tile.y + 1};
					dir = Change::Left;
					max_y -= 1;
		case Left:  if (tile.x > min_x)
						return {tile.x - 1, tile.y};
					dir = Change::Up;
					min_x += 1;
		case Up:    if (tile.y > min_y)
						return {tile.x, tile.y - 1};
					dir = Change::Right;
					min_y += 1;
	}
	return next(tile);
}

void SnailFill::init_coords(const int side) {
	min_x = 0;
	min_y = 1;
	max_x = side - 1;
	max_y = side - 1;
	center.assign(side / 2 - !(side & 1), side / 2);
}

Grid SnailFill::get_goal_state(const Grid& g) {
	init_coords(g.side);
	Grid goal;
	goal.side = g.side;
	for (ft::coords tile{0, 0}; int val : get_puzzle_values(g)) {
		goal[tile] = val;
		tile = next(tile);
	}
	return goal;
}


}
