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

/*
Node::Node(Grid g, int p, Nodeptr par)
	: grid(std::move(g))
	, priority(p)
	, parent(std::move(par)) {}

Nodeptr make_node(Grid g, int p, Nodeptr par)
{
	return std::make_shared<Node>(std::move(g), p, par);
}

std::size_t hash_node::operator()(const Node& n) const
{
	std::size_t hash = 17;
	auto coords_hash = hash_coords{};
	auto int_hash = std::hash<int>{};
	for (const auto& [coords, val]  : n.grid.grid) {
		hash = hash * 31 + coords_hash(coords) + int_hash(val);
	}
	return hash;
}

std::size_t hash_node::operator()(Nodeptr n) const
{
	return hash_node::operator()(*n);
}
*/

}
