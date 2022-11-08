#pragma once

#include <vector>
#include <iostream>
#include <random>

#include "sort_system.h"

// this sort is a joke

class BogoSortSystem : public SortSystem {

	unsigned int step = 0;
	bool shuffling = true;
	bool sorted = true;

public:



	IterInfo iterate() override {
		IterInfo it(0, 0);
		if (shuffling) {

			std::uniform_int_distribution<unsigned int> gen(0, sort.size() - 1); // uniform, unbiased
			unsigned int rIndex = gen(rng);
			swap(step, rIndex);
			it.swapFst = step;
			it.swapSnd = rIndex;

			if (step >= sort.size() - 1) {
				step = 0;
				shuffling = false;
				return it;
			}

			step++;

		}
		else {

			if (sort[step] > sort[step + 1])
				sorted = false;
			if (step >= sort.size() - 2)
				if (sorted) {
					si.done = true;
					return it;
				}
				else {
					sorted = true;
					step = 0;
					shuffling = true;
					return it;
				}
			step++;
		}
		return it;
	}

	BogoSortSystem(std::vector<unsigned int>& array) : SortSystem(array) {}
};