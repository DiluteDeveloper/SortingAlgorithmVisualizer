#pragma once

#include <vector>
#include <imgui/imgui.h>
#include <random>


struct SortData {
	uint64_t swaps = 0;
	uint64_t array_accesses = 0;

	const std::string_view name = "Default sort";

	SortData(std::string_view name) : name(name) {}

	void reset() {
		array_accesses = 0;
		swaps = 0;
	}
};

// bool and if operator overloaded for checking if array was sorted on this operation
struct ComparisonData {
	uint16_t a = 0, b = 0;
	uint16_t prevA = 0, prevB = 0;

	enum class Status {
		SWAP = 0,
		COMPARISON = 1,
		DONE = 2
	} status = Status::DONE;

	ComparisonData(uint16_t a, uint16_t b, uint16_t prevA, uint16_t prevB, ComparisonData::Status status)
		: a(a), b(b), prevA(prevA), prevB(prevB), status(status) { }

	ComparisonData() = default;
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
