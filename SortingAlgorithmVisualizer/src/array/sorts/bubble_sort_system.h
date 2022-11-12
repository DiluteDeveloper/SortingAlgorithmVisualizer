#pragma once

#include <vector>
#include <iostream>

#include "sort_system.h"

class BubbleSortSystem : public SortSystem {

	uint16_t step = 0;
	uint16_t prevA = 0;
	uint16_t prevB = 0;

	bool swapStatus = false; // Have we swapped yet this iteration? if we get to the end and we havent, its done!

public:

	ComparisonData iterate() override {
		ComparisonData::Status status = ComparisonData::Status::DONE;
		if (step >= (sArray.size() - 1) - sData.iterations) // condition true if at end of iteration
		{
			sData.iterations++;
			if (!swapStatus) // done!
				goto conclusion;
			swapStatus = false;

			step = 0;
		}
		sData.comparisons++;
		if (sArray[step] > sArray[step + 1]) {

			swapStatus = true;
			sData.swaps++;


			status = ComparisonData::Status::SWAP;
		} else
			status = ComparisonData::Status::COMPARISON;

	conclusion:
		ComparisonData cd(step, static_cast<uint16_t>(step + 1), prevA, prevB, status);
		prevA = cd.a;
		prevB = cd.b;
		step++;
		return cd;
	}
	
	BubbleSortSystem(std::vector<float>& sArray) : SortSystem(sArray, "Bubble Sort") {  }
	void reset() override {
		step = 0;
		swapStatus = false;
		sData.reset();
	}
};