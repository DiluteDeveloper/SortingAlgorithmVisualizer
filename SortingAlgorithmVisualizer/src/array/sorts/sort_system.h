#pragma once

#include <vector>
#include <imgui/imgui.h>
#include <random>


struct SortData {
	uint64_t swaps = 0;
	uint64_t array_accesses = 0;
	
	double beginTime = ImGui::GetTime();

	const std::string_view name = "Default sort";

	SortData(std::string_view name) : name(name) {}

	void reset() {
		array_accesses = 0;
		swaps = 0;
	}
};

enum class SwapStatus {
	SWAP = 0,
	COMPARISON = 1,
	DONE = 2
};


struct ComparisonData {
	uint16_t a = 0, b = 0, c = 0;
	bool paintStatus = false;
	SwapStatus status;

	ComparisonData() = default;

	void set(uint16_t in_a, uint16_t in_b) { a = in_a; b = in_b; }
	void set(uint16_t in_a, uint16_t in_b, uint16_t in_c) { a = in_a; b = in_b; c = in_c; }
};

class SortSystem {
protected:
	std::vector<float>& sArray;

public:
	virtual ComparisonData iterate() = 0;

	SortData sData;
	SortSystem(std::vector<float>& sArray, const std::string_view& name) : sArray(sArray), sData(name) { }

	// Setup as if a whole new array came in
	virtual void reset() = 0;
};
