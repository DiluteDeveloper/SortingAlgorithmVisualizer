#pragma once

#include "sort_system.h"

#include <iostream>

class CycleSortSystem : public SortSystem {

	uint16_t step = 0;
	uint16_t prev = 0;

public:

	ComparisonData iterate() override {
		ComparisonData cd;

		if(prev>0)
			cd.paintStatus = true;

		cd.set(step, sArray[step], prev);

		sData.array_accesses += 2;
		if (sArray[step] != step) {
			cd.status = SwapStatus::SWAP;
			sData.swaps++;
			prev = sArray[step];
		}
		else {
			prev = 0;
			cd.status = SwapStatus::COMPARISON;
			step++;
			if (step > sArray.size() - 1)
				cd.status = SwapStatus::DONE;
		}



		return cd;
	}

	CycleSortSystem(std::vector<float>& sArray) : SortSystem(sArray, "Cycle Sort") {  }
	void reset() override {
		step = 0;
		sData.reset();
	}
};
