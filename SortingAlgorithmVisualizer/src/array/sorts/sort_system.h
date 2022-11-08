#pragma once

#include <vector>
#include <imgui/imgui.h>
#include <random>

#include "rendering/array_renderer.h"


struct SortData {
	uint64_t iterations = 0;
	uint64_t swaps = 0;
	uint64_t comparisons = 0;

	std::string_view name = "Default sort";
};

// bool and if operator overloaded for checking if array was sorted on this operation
struct OperationData {
	uint16_t swapFst = 0, swapSnd = 0;

	OperationData(uint16_t swapFst, uint16_t swapSnd) : swapFst(swapFst), swapSnd(swapSnd) {}
	OperationData() = default;

	operator bool() const {
		return (swapFst == swapSnd);
	}
};

class SortSystem {
protected:
	std::vector<uint16_t>& sArray;

	void swap(uint16_t a, uint16_t b) {
		sData.swaps++;

		uint16_t temp = sArray[a];
		sArray[a] = sArray[b];
		sArray[b] = temp;
	}


public:
	virtual OperationData iterate() = 0;

	SortData sData;
	SortSystem(std::vector<uint16_t>& sArray) : sArray(sArray) { }

};
