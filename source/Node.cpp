#include "Node.hpp"

namespace ft {

Node::Node(Grid g, int gs, int fs, Nodeptr par)
	: grid(std::move(g))
	, g_score(gs)
	, f_score(fs)
	, parent(par) {}

Nodeptr make_node(Grid g, int gs, int fs, Nodeptr par)
{
	return std::make_shared<Node>(std::move(g), gs, fs, par);
}

}
