#pragma once
#include "coords.hpp"
#include <unordered_map>
#include <vector>
#include <initializer_list>

namespace ft {

enum class Change {
	Up,
	Down,
	Right,
	Left
};

std::ostream& operator<< (std::ostream& os, Change c);

struct Grid {
	std::unordered_map<coords, int, ft::hash_coords> grid;
	int side;

	using value_type = decltype(grid)::value_type;

	Grid(std::initializer_list<std::pair<coords, int>> vals);
	Grid(const Grid& other);
	Grid(Grid&& other);
	Grid& operator= (const Grid& other);
	Grid& operator= (Grid&& other);
	Grid() = default;

	auto begin() { return grid.begin(); }
	auto begin() const { return grid.begin(); }
	auto end() { return grid.end(); }
	auto end() const { return grid.end(); }

	int at(const ft::coords& tile) const;
	int& operator[](const ft::coords& tile);

	void print() const noexcept;

	auto get_neighbor(const ft::coords& tile, Change dir) noexcept -> decltype(grid)::iterator;
	auto get_neighbors_of_empty() -> std::vector<decltype(grid)::iterator>;

	auto find(const ft::coords& c) noexcept -> decltype(grid)::iterator;
	auto find(const ft::coords& c) const noexcept -> decltype(grid)::const_iterator;
	auto find(int val) noexcept -> decltype(grid)::iterator;
	auto find(int val) const noexcept -> decltype(grid)::const_iterator;
};

}

namespace std {
	void swap(ft::Grid::value_type& lhs, ft::Grid::value_type& rhs) noexcept;
}
