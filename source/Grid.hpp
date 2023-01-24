#pragma once

#include "Coords.hpp"

#include <initializer_list>
#include <unordered_map>
#include <vector>
#include <memory>

namespace ft {

enum class Change {
	Up,
	Down,
	Right,
	Left
};

struct Grid
{
	using grid_t = std::unordered_map<ft::coords, int, hash_coords>;
	using iter_t = grid_t::iterator;
	using const_iter_t = grid_t::const_iterator;

	grid_t grid;
	const int side;

	Grid(std::initializer_list<grid_t::value_type> vals);

	bool operator== (const Grid& other) const = default;
	int at(coords tile) const;
	int& operator[](coords tile) noexcept;

	auto neighbor(coords tile, Change dir) noexcept -> iter_t;
	auto neighbors_of_empty() -> std::vector<iter_t>;

	auto find_by_coords(coords tile) noexcept -> iter_t;
	auto find_by_coords(coords tile) const noexcept -> const_iter_t;

	auto find_by_value(int val) noexcept -> iter_t;
	auto find_by_value(int val) const noexcept -> const_iter_t;

	auto swap_empty_with(int val) noexcept -> void;

	void print() const;

	int get_print_width() const;
};

}

namespace std {
	void swap(ft::Grid::iter_t a, ft::Grid::iter_t b);
}
