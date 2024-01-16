#pragma once

#include "sort_system.h"

// less efficient version of insertion sort
class GnomeSortSystem : public SortSystem {

	uint32_t step = 0;

public:


	// Rewriting from scratch;
	ComparisonData iterate() override {
		ComparisonData cd;

		if (step == sArray.size())
			cd.status = SwapStatus::DONE;
		sData.array_accesses++;
		if (sArray[step] > sArray[step + 1]) {
			cd.a = step;
			cd.b = step + 1;
			if(step>0)
				step -= 1;
			cd.status = SwapStatus::SWAP;
			sData.swaps++;
		}
		else {
			if ((step + 2) == sArray.size()) {
				cd.status = SwapStatus::DONE;
				goto end;
			}
			cd.a = step;
			cd.b = step + 1;

			step += 1;
			cd.status = SwapStatus::COMPARISON;

		}
		end:
		return cd;
	}

	GnomeSortSystem(std::vector<float>& sArray) : SortSystem(sArray, "Gnome Sort") {  }
	void reset() override {
		step = 0;
		sData.reset();
	}
};