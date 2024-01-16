#pragma once

#include "sort_system.h"

class BubbleSortSystem : public SortSystem {

	uint16_t step = 0;
	uint16_t iteration = 0;

public:


	// Rewriting from scratch;
	ComparisonData iterate() override {
		ComparisonData cd;
		if (iteration == sArray.size() - 1) {
			cd.status = SwapStatus::DONE;
			return cd;
		}
		else if (step == (sArray.size() - 1) - iteration) {
			step = 0;
			iteration++;
		}


		cd.set(step, static_cast<uint16_t>(step + 1));

		sData.array_accesses += 2;
		if (sArray[step] > sArray[step + 1]) {
			cd.status = SwapStatus::SWAP;
			sData.swaps++;

		}

		else cd.status = SwapStatus::COMPARISON;

		step++;
		return cd;
	}
	
	BubbleSortSystem(std::vector<float>& sArray) : SortSystem(sArray, "Bubble Sort") {  }
	void reset() override {
		step = 0;
		iteration = 0;
		sData.reset();
	}
};