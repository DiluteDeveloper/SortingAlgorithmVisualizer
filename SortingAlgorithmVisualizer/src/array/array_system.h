#pragma once

#include "sorts/sort_system.h"

#include <memory>
#include <iostream>

#include "rendering/2D/array_mesh.h"

/* Responsibilities

Hold onto the array object
Handle rendering of the array object
Handle sorting of the array object
is 1:1 with its array object

*/ 
class ArraySystem {
	friend class GUISystem;
	std::vector<float> sArray;
	bool done = false;

	std::unique_ptr<SortSystem> sortSystem;
public:

	ArrayMesh2D mesh;

	ArraySystem() = default;

	template<typename T>
	void SetSorter() {
		sortSystem.reset();
		sortSystem = std::make_unique<T>(sArray);
	}
	SortData getSortData() { return sortSystem->sData; }
	ComparisonData sort();

	void shuffle();
	void generateArray(uint16_t numElements);
};
