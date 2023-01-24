#pragma once
#include <initializer_list>
#include <utility>
#include <ostream>

namespace ft {
	struct coords {
		int x = -1;
		int y = -1;

		coords() = default;
		coords(int x, int y);
		coords(std::initializer_list<int> list);
		auto operator<=>(const coords&) const = default;
		coords& assign(int a, int b);

		friend std::ostream& operator<< (std::ostream& os, const coords& c);
	};

	struct hash_coords {
		std::size_t operator()(const coords& c) const;
	};

	coords make_coords(int x, int y);
}
