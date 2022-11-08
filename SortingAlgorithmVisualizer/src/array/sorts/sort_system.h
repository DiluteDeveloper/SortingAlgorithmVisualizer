#pragma once

#include <vector>
#include <imgui/imgui.h>
#include <random>

#include "rendering/array_renderer.h"

// move 'done' to array_system, different sorters will lose that info

extern std::mt19937 rng;
struct SortInfo {
	unsigned int swaps = 0;
	unsigned int comparisons = 0;
	unsigned int iterations = 0;

	bool done = false;
};

struct IterInfo {
	unsigned int swapFst = 0, swapSnd = 0;

	IterInfo(unsigned int swapFst, unsigned int swapSnd) : swapFst(swapFst), swapSnd(swapSnd) {}

	operator bool() const {
		return (swapFst != swapSnd);
	}
};

class SortSystem {
protected:
	std::vector<unsigned int>& sort;

	void swap(unsigned int a, unsigned int b) {
		si.swaps++;

		unsigned int temp = sort[a];
		sort[a] = sort[b];
		sort[b] = temp;
	}


public:
	virtual IterInfo iterate() { si.done = true; return IterInfo{ 0,0 }; };

	SortInfo si;
	SortSystem(std::vector<unsigned int>& array) : sort(array) { }

};
