#pragma once

#include <vector>
#include <iostream>

#include "sort_system.h"

class BubbleSortSystem : public SortSystem {

	uint16_t step = 0;

	bool swapStatus = false; // Have we swapped yet this iteration? if we get to the end and we havent, its done!

public:

	OperationData iterate() override {
		OperationData oData;

		while (true) {

			if (step >= (sArray.size() - 1) - sData.iterations) // condition true if at end of iteration
			{
				sData.iterations++;
				if (!swapStatus) // done!
					break;
				swapStatus = false;

				step = 0;
			}

			sData.comparisons++;
			if (sArray[step] > sArray[step + 1]) {

				swap(step, step + 1);
				swapStatus = true;

				oData.swapFst = step; 
				oData.swapSnd = (step + 1);
				return oData;
				
			}
			step++;
		}
		return oData;
	}
	
	BubbleSortSystem(std::vector<uint16_t>& sArray) : SortSystem(sArray) { sData.name = "Bubble Sort"; }
};