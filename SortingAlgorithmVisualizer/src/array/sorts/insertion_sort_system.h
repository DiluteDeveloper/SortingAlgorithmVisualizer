#pragma once

#include "sort_system.h"

class InsertionSortSystem : public SortSystem {

	uint16_t stepFwd = 0;
	uint16_t stepBwd = 0;

	bool fwd = true;

public:

	// Rewriting from scratch;
	// something wrong with this
	ComparisonData iterate() override {
		ComparisonData cd;
		cd.status = SwapStatus::COMPARISON;

		if (fwd) {
			if (stepFwd == sArray.size() - 1) {
				cd.status = SwapStatus::DONE;
				return cd;
			}

			cd.set(stepFwd, static_cast<uint16_t>(stepFwd + 1));

			sData.array_accesses += 2;
			if (sArray[stepFwd] > sArray[stepFwd + 1]) {
				cd.status = SwapStatus::SWAP;
				sData.swaps++;

				if (stepFwd - 1 >= 0) {
					fwd = false;
					stepBwd = stepFwd;
				}

			}
			stepFwd++;
			return cd;
		}
		else {
			cd.set(stepBwd, static_cast<uint16_t>(stepBwd - 1));
			sData.array_accesses += 2;
			if (sArray[stepBwd] < sArray[stepBwd - 1]) {
				cd.status = SwapStatus::SWAP;
				sData.swaps++;
			}
			else {
				fwd = true;
				return cd;
			}
			if (stepBwd - 1 <= 0)
				fwd = true;

			stepBwd--;

			return cd;
		}
	}


	InsertionSortSystem(std::vector<float>& sArray) : SortSystem(sArray, "Insertion Sort") {  }
	void reset() override {
		stepFwd = 0;
		stepBwd = 0;
		fwd = true;
		sData.reset();
	}
};