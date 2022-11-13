#pragma once

#include "sort_system.h"

class SelectionSortSystem : public SortSystem {

	uint16_t backStep = 0;
	uint16_t lowestStep = 0;
	uint16_t step = 0;


	uint16_t prevA = 0;
	uint16_t prevB = 0;

	ComparisonData cd;

	void checkNextLowest() {
		if (sArray[step] < sArray[lowestStep]) {
			sData.array_accesses += 2;
			lowestStep = step;
		}
		step++;
	}

public:

	ComparisonData iterate() override {
		cd.status = ComparisonData::Status::COMPARISON;
		cd.prevA = prevA;
		cd.prevB = prevB;
		cd.a = backStep;
		cd.b = lowestStep;
		prevA = cd.a;
		prevB = cd.b;
		if (step == sArray.size()) {
			cd.status = ComparisonData::Status::SWAP;
			sData.swaps++;
			lowestStep = backStep + 1;
			backStep++;
			step = backStep + 1;
		}
		if (backStep == sArray.size() - 2) {
			cd.status = ComparisonData::Status::DONE;
		}

		checkNextLowest();
		return cd;
	}

	SelectionSortSystem(std::vector<float>& sArray) : SortSystem(sArray, "Selection Sort") {  }
	void reset() override {
		step = 0;
		backStep = 0;
		prevA = 0;
		prevB = 0;
		sData.reset();
	}
};
