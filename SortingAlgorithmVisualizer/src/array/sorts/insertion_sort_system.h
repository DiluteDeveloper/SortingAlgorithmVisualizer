#pragma once

#include "sort_system.h"

class InsertionSortSystem : public SortSystem {

	uint16_t step = 0;
	uint16_t backStep = 0;
	uint16_t prevA = 0;
	uint16_t prevB = 0;

	ComparisonData cd;

	bool backStepping = false;

	void tryBackStep() { // returns whether backstepping is done

		cd.a = backStep;
		cd.b = backStep - 1;
		cd.prevA = prevA;
		cd.prevB = prevB;
		prevA = cd.a;
		prevB = cd.b;



		if (sArray[backStep] < sArray[backStep - 1]) {
			backStep--;
			cd.status = ComparisonData::Status::SWAP;
			sData.swaps++;
			sData.array_accesses += 2;
		} else {
			cd.status = ComparisonData::Status::COMPARISON;
			backStepping = false;
		}
	}

	void tryStepForward() {

		cd.a = step;
		cd.b = step + 1;
		cd.prevA = prevA;
		cd.prevB = prevB;
		prevA = cd.a;
		prevB = cd.b;

		if (step >= sArray.size() - 1) {
			cd.status = ComparisonData::Status::DONE;
			return;
		}

		if (sArray[step] > sArray[step + 1]) {
			backStepping = true;
			backStep = step;
			step++;
			cd.status = ComparisonData::Status::SWAP;
			sData.array_accesses += 2;
			sData.swaps++;
		}
		else {
			cd.status = ComparisonData::Status::COMPARISON;
			step++;
		}			


	}

public:

	ComparisonData iterate() override {
		if (backStepping && backStep > 0) {
			tryBackStep();
		}
		else {
			tryStepForward();
		}
		return cd;
	}

	InsertionSortSystem(std::vector<float>& sArray) : SortSystem(sArray, "Insertion Sort") {  }
	void reset() override {
		step = 0;
		prevA = 0;
		prevB = 0;
		backStepping = true;
		sData.reset();
	}
};


/*
	bool tryBackStep() { // returns whether backstepping is done

		if (backStep == 0) {
			backStepping = false;
			return false;
		}
		if (sArray[backStep] < sArray[backStep - 1]) {
			backStep--;
		}
		else {
			backStepping = false;
			return false;
		}


	}

	bool tryStepForward() {
		if (sArray[step] > sArray[step + 1]) {
			backStepping = true;
			backStep = step;
			step++;
			return true;
		}
		step++;
		return false;



	}

public:

	ComparisonData iterate() override {
		ComparisonData cd;
		cd.status = ComparisonData::Status::COMPARISON;
		cd.prevA = prevA;
		cd.prevB = prevB;
		std::cout << step << std::endl;
		if (backStepping) {
			cd.a = backStep;
			cd.b = backStep - 1;
			if (tryBackStep()) {
				cd.status = ComparisonData::Status::SWAP;
			}
			else {

				if (step == 149)
					int i = 5;
				if (step >= sArray.size() - 2) {

					cd.status = ComparisonData::Status::DONE;
					return cd;
				}
				if (tryStepForward()) {
					cd.status = ComparisonData::Status::SWAP;
					cd.a = step;
					cd.b = step + 1;
					goto conclusion;
				}

			}
			goto conclusion;
		}
		else {
			if (step >= sArray.size() - 2) {

				cd.status = ComparisonData::Status::DONE;
				return cd;
			}
			if (tryStepForward()) {
				cd.status = ComparisonData::Status::SWAP;
			}

			goto conclusion;
		}

	conclusion:
		prevA = cd.a;
		prevB = cd.b;
		return cd;

	}*/