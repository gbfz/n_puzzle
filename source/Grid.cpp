#include "Grid.hpp"
#include <initializer_list>
#include <algorithm>
#include <cmath>
#include <utility>
#include <iomanip>
#include <iostream>

namespace ft {

Grid::Grid(std::initializer_list<grid_t::value_type> vals)
	: grid(std::move(vals))
	, side(std::sqrt(vals.size() + 1)) {}

int Grid::at(coords tile) const
{
	return grid.at(tile);
}

int& Grid::operator[](coords tile) noexcept
{
	return grid[tile];
}

auto Grid::neighbor(coords tile, Change dir) noexcept -> iter_t
{
	using enum Change;
	switch (dir)
	{
		case Up:    tile.y -= 1; break;
		case Down:  tile.y += 1; break;
		case Left:  tile.x -= 1; break;
		case Right: tile.x += 1; break;
	}
	return grid.find(tile);
}

auto Grid::neighbors_of_empty() -> std::vector<iter_t>
{
	auto [empty_tile, _] = *this->find_by_value(0);
	std::vector<iter_t> neighbors;

	if (auto right = neighbor(empty_tile, Change::Right); right != grid.end()) {
		neighbors.emplace_back(std::move(right));
	}
	if (auto down = neighbor(empty_tile, Change::Down); down != grid.end()) {
		neighbors.emplace_back(std::move(down));
	}
	if (auto left = neighbor(empty_tile, Change::Left); left != grid.end()) {
		neighbors.emplace_back(std::move(left));
	}
	if (auto up = neighbor(empty_tile, Change::Up); up != grid.end()) {
		neighbors.emplace_back(std::move(up));
	}
	return neighbors;
}

auto Grid::find_by_coords(coords tile) noexcept -> iter_t
{
	return grid.find(tile);
}

auto Grid::find_by_coords(coords tile) const noexcept -> const_iter_t
{
	return grid.find(tile);
}

auto Grid::find_by_value(int val) noexcept -> iter_t
{
	return std::ranges::find_if(grid, [val](const auto& p) {
			return p.second == val;
	});
}

auto Grid::find_by_value(int val) const noexcept -> const_iter_t
{
	return std::ranges::find_if(grid, [val](const auto& p) {
			return p.second == val;
	});
}

int Grid::get_print_width() const
{
	int longest_num = std::ranges::max_element(grid)->second;
	int num_digits = longest_num > 9 ? std::log10(longest_num) + 1 : 1;
	return num_digits + 1;
}

void Grid::print() const
{
	const int len = get_print_width();
	std::cout << " x";
	for (auto i = 0; i < side; ++i) {
		std::cout << std::setw(len + 1) << " . ";
	}
	std::cout << '\n';
	for (auto i = 0; i < side; ++i)
	{
		std::cout << " .";
		for (auto j = 0; j < side; ++j) {
			if (grid.contains({j, i}))
			{
				auto val = grid.at({j, i});
				if (val == 0) {
					std::cout << "\033[1;31m" // red
						      << std::setw(len) << val
							  << "\033[0m "; // reset
				} else {
					std::cout << std::setw(len) << val << ' ';
				}
			}
		}
		std::cout << '\n';
	}
}

auto Grid::swap_empty_with(int val) noexcept -> void
{
	auto empty_tile = find_by_value(0);
	auto swap_tile  = find_by_value(val);
	std::swap(empty_tile->second, swap_tile->second);
}

}

namespace std {
	void swap(ft::Grid::iter_t a, ft::Grid::iter_t b) {
		std::swap(a->second, b->second);
	}
}
