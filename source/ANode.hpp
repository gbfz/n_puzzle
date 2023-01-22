#pragma once
#include "Grid.hpp"
#include <memory>

namespace ft {

struct ANode {
	std::shared_ptr<Grid> parent;
	std::size_t f_score;
	std::size_t h_score;
	static constexpr std::size_t g_score = 1;
};

}
