#pragma once
#include "Grid.hpp"
#include <memory>

namespace ft {

struct Node;
using Nodeptr = std::shared_ptr<Node>;

Nodeptr make_node(Grid g, int gs, int fs, Nodeptr par);

struct Node
{
	Grid grid;
	int g_score;
	int f_score;
	Nodeptr parent;

	Node(Grid g, int gs, int fs, Nodeptr par);
};

}
