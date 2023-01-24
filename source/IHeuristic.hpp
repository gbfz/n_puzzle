#pragma once
#include "Grid.hpp"
#include <vector>

namespace ft {

struct IHeuristic {
	virtual int f_score(ft::coords, ft::coords) noexcept = 0;

	virtual int h_score(const Grid& current, const Grid& goal) noexcept = 0;
	virtual int h_score(ft::coords, ft::coords) noexcept = 0;


	virtual ~IHeuristic() {}
};

}
