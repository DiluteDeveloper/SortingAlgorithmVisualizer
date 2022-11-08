#pragma once

#include "sorts/sort_system.h"
#include "rendering/array_renderer.h"

#include <memory>
#include <iostream>

/* Responsibilities

Hold onto the array object
Handle rendering of the array object
Handle sorting of the array object
is 1:1 with its array object

*/ 
class ArraySystem {
	std::vector<uint16_t> arrayObj;

	std::unique_ptr<ArrayRenderer> aRenderer;
	std::unique_ptr<SortSystem> sortSystem;


public:

	bool aSorted = false;

	RenderOptions& getRenderOptions() { 
		return aRenderer->rOptions;
	}

	ArraySystem(uint16_t numElements, uint16_t heightComplexity);

	template<typename T>
	void SetSorter() {
		sortSystem.reset();
		sortSystem = std::make_unique<T>(arrayObj);
	}
	SortData getSortData() { return sortSystem->sData; }
	OperationData sort();
	void render();
	void updateMesh();
};
