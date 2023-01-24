#pragma once
#include "Grid.hpp"
#include <memory>

namespace ft {

struct Node;
using Nodeptr = std::shared_ptr<Node>;

/*
struct Node
{
	Grid grid;
	int priority;
	Nodeptr parent;

	Node(Grid g, int p, Nodeptr par);
};

Nodeptr make_node(Grid g, int p, Nodeptr par);

struct hash_node {
	std::size_t operator()(const Node& n) const;
	std::size_t operator()(Nodeptr n) const;
};
*/

struct Node
{
	Grid grid;
	int g_score;
	int f_score;
	Nodeptr parent;

	Node(Grid g, int gs, int fs, Nodeptr par);
};

Nodeptr make_node(Grid g, int gs, int fs, Nodeptr par);

}
