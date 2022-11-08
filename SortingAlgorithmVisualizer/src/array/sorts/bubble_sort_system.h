#pragma once

#include <vector>
#include <iostream>

#include "sort_system.h"

class BubbleSortSystem : public SortSystem {

	unsigned int step = 0;
	unsigned int furthestSwapIndex = (unsigned int)sort.size() - 2;
	unsigned int iterateFSI = 0;

	bool hasSwapped = false;
	bool swapCheck = false;

public:

	IterInfo iterate() override {

		if (swapCheck) {
			if (step >= furthestSwapIndex) {
				si.iterations++;
				if (!hasSwapped) {
					si.done = true;
					return IterInfo{ 0,0 };
				}
				hasSwapped = false;

				furthestSwapIndex = iterateFSI;
				iterateFSI = 0;
				step = 0;


			}
		}
		else
			if (step >= sort.size() - 1) {
				si.iterations++;
				swapCheck = true;
				if (!hasSwapped) {
					si.done = true;
					return IterInfo{ 0,0 };
				}

				hasSwapped = false;
				furthestSwapIndex = iterateFSI;
				iterateFSI = 0;
				step = 0;
			}

		IterInfo i(0,0);
		si.comparisons++;
		if (sort[step] > sort[step + 1]) {
			swap(step, step + 1);
			hasSwapped = true;

			if(step > iterateFSI)
				iterateFSI = step;

			i.swapFst = step;
			i.swapSnd = step + 1;
		}
		step++;

		return i;
	}
	
	BubbleSortSystem(std::vector<unsigned int>& array) : SortSystem(array) {}
};