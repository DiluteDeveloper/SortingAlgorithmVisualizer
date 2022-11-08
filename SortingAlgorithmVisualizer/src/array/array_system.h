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
	std::vector<unsigned int> arrayObj;

	std::unique_ptr<ArrayRenderer> ar;
	std::unique_ptr<SortSystem> sortAlg;


public:
	RenderOptions& getRenderOptions() { 
		return ar->ro;
	}

	ArraySystem(unsigned int numElements, unsigned int heightComplexity);

	template<typename T>
	void SetSorter() {
		sortAlg.reset();
		sortAlg = std::make_unique<T>(arrayObj);
	}
	SortInfo getSortInfo() { return sortAlg->si; }
	IterInfo sort();
	void render();
	void updateMesh();
};
