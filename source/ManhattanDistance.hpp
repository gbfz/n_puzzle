#pragma once
#include "IHeuristic.hpp"

namespace ft {

struct ManhattanDistance : virtual IHeuristic {

	// get misplaced tiles coordinates and their place in goal state
	std::vector<std::pair<ft::coords, ft::coords>> misplaced_tiles(const Grid& current, const Grid& goal)
	{
		std::vector<std::pair<ft::coords, ft::coords>> misplaced;
		for (auto [coords, val] : current.grid) {
			if (val == 0)
				continue;
			// auto goal_coords = goal.find_by_coords(coords)->first;
			auto goal_coords = goal.find_by_value(val)->first;
			if (coords != goal_coords) {
				misplaced.emplace_back(std::move(coords), goal_coords);
			}
		}
		return misplaced;
	}

	virtual int h_score(const Grid& current, const Grid& goal) noexcept override
	{
		int sum = 0;
		for (auto&& candidate : misplaced_tiles(current, goal)) {
			sum += h_score(candidate.first, candidate.second);
		}
		return sum;
	}

	virtual int h_score(ft::coords fst, ft::coords snd) noexcept override
	{
		using std::abs;
		return abs(fst.x - snd.x) + abs(fst.y - snd.y);
	}

	virtual int f_score(ft::coords fst, ft::coords snd) noexcept override
	{
		return h_score(std::move(fst), std::move(snd)) + 1;
	}
};

}
