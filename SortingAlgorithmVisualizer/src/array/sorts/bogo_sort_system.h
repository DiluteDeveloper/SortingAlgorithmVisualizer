#pragma once
#include <random>

#include "sort_system.h"


// this sort is a joke
class BogoSortSystem : public SortSystem {

	unsigned int step = 0;
	bool shuffling = false;
	uint16_t prevA = 0;
	uint16_t prevB = 0;
	std::mt19937 rng;
	bool swapStatus = false;

public:

	ComparisonData iterate() override {
		ComparisonData cd;
		cd.prevA = prevA;
		cd.prevB = prevB;
		if (shuffling) {
			cd.status = ComparisonData::Status::SWAP;
			sData.swaps++;
			std::uniform_int_distribution<unsigned int> gen(0, sArray.size() - 1); // uniform, unbiased
			unsigned int rIndex = gen(rng);
			cd.a = step;
			cd.b = rIndex;
			prevA = step;
			prevB = rIndex;
			if (step >= sArray.size() - 1) {
				step = 0;
				shuffling = false;
				return cd;
			}
			step++;
			return cd;

		}
		else {
			cd.status = ComparisonData::Status::COMPARISON;
			cd.a = step;
			cd.b = static_cast<uint16_t>(step + 1);
			prevA = cd.a;
			prevB = cd.b;

			if (sArray[step] > sArray[step + 1]) {
				swapStatus = true;
				sData.array_accesses += 2;
			}


			if (step >= sArray.size() - 2) {
				if (!swapStatus) {
					cd.status = ComparisonData::Status::DONE;
				}
				else {
					swapStatus = false;
					step = 0;
					shuffling = true;
					rng.seed(time(nullptr));

				}
			}
			step++;
			return cd;

		}
	}

	BogoSortSystem(std::vector<float>& sArray) : SortSystem(sArray, "Bogo Sort") {  }
	void reset() override {
		step = 0;
		shuffling = false;
		prevA = 0;
		prevB = 0;

		bool swapStatus = false;

	}
};