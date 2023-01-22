#include "coords.hpp"
#include "Grid.hpp"
#include <algorithm>
#include <bits/ranges_util.h>
#include <cmath>
#include <iostream>

namespace ft {

Grid::Grid(std::initializer_list<std::pair<coords, int>> vals)
	: side(std::sqrt(vals.size() + 1.0))
{
	for(auto&& pair : vals) {
		grid.emplace(std::move(pair));
	}
}

Grid::Grid(const Grid& other)
	: grid(other.grid)
	, side(other.side) {
}

Grid::Grid(Grid&& other) { *this = std::move(other); }

Grid& Grid::operator= (const Grid& other) {
	if (this == &other)
		return *this;
	grid = other.grid;
	side = other.side;
	return *this;
}

Grid& Grid::operator= (Grid&& other) {
	if (this == &other)
		return *this;
	grid = std::move(other.grid);
	side = std::exchange(other.side, 0);
	return *this;
}

int Grid::at(const ft::coords& tile) const { return grid.at(tile); }
int& Grid::operator[](const ft::coords& tile) { return grid[tile]; }

void Grid::print() const noexcept {
	std::cout << " x";
	// TODO: select number of spaces according to grid size
	for (auto i = 0; i < this->side; ++i) {
		std::cout << " .";
	}
	std::cout << '\n';
	for (auto i = 0; i < this->side; ++i) {
		std::cout << " . ";
		for (auto j = 0; j < this->side; ++j) {
			if (grid.contains({j, i}))
				std::cout << grid.at({j, i}) << ' ';
			else std::cout << "  ";
		}
		std::cout << '\n';
	}
}

auto Grid::get_neighbor(const ft::coords& tile, Change dir) noexcept
	-> decltype(grid)::iterator
{
	auto x = tile.x;
	auto y = tile.y;
	switch (dir) {
		case Change::Up:    y -= 1; break;
		case Change::Down:  y += 1; break;
		case Change::Left:  x -= 1; break;
		case Change::Right: x += 1; break;
	}
	return grid.find({x, y});
}

auto Grid::get_neighbors_of_empty()
	-> std::vector<decltype(grid)::iterator>
{
	auto [empty_tile, _] = *find(0);
	std::vector<decltype(grid)::iterator> neighbors;
	if (auto&& up = get_neighbor(empty_tile, Change::Up); up != grid.end()) {
		neighbors.emplace_back(up);
	}
	if (auto&& right = get_neighbor(empty_tile, Change::Right); right != grid.end()) {
		neighbors.emplace_back(right);
	}
	if (auto&& down = get_neighbor(empty_tile, Change::Down); down != grid.end()) {
		neighbors.emplace_back(down);
	}
	if (auto&& left = get_neighbor(empty_tile, Change::Left); left != grid.end()) {
		neighbors.emplace_back(left);
	}
	return neighbors;
}

auto Grid::find(const ft::coords& c) noexcept
	-> decltype(grid)::iterator
{ return grid.find(c); }

auto Grid::find(const ft::coords& c) const noexcept
	-> decltype(grid)::const_iterator
{ return grid.find(c); }

auto Grid::find(int val) noexcept
	-> decltype(grid)::iterator
{
	return std::ranges::find_if(grid, [val](const auto& p) { return p.second == val; });
}

auto Grid::find(int val) const noexcept
	-> decltype(grid)::const_iterator
{
	return std::ranges::find_if(grid, [val](const auto& p) { return p.second == val; });
}

std::ostream& operator<< (std::ostream& os, Change c) {
	using enum Change;
	switch (c) {
		case Up:    return os << "Up";
		case Right: return os << "Right";
		case Down:  return os << "Down";
		case Left:  return os << "Left";
	}
	return os;
}

}

namespace std {
	void swap(ft::Grid::value_type& lhs, ft::Grid::value_type& rhs) noexcept {
		std::swap(lhs.second, rhs.second);
	}
}
