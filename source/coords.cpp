#include "coords.hpp"
#include <iterator>
#include <iostream>

namespace ft {

	coords::coords(int x, int y)
		: x(x), y(y) {
	}

	coords::coords(std::initializer_list<int> list)
		: x(*list.begin())
		, y(*std::next(list.begin())) {
	}

	coords& coords::assign(int a, int b) { x = a; y = b; return *this; }

	std::ostream& operator<< (std::ostream& os, const coords& c) {
		return os << "{" << c.x << ", " << c.y << "}";
	}

	std::size_t hash_coords::operator()(const coords& c) const {
		auto h = std::hash<int>{};
		uintmax_t hash = h(c.x);
        hash <<= sizeof(uintmax_t) * 4;
        hash ^= h(c.y);
        return h(hash);}

	coords make_coords(int x, int y) { return {x, y}; }
}
