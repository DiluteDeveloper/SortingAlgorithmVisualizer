#include <random>

#include "array/array_system.h"

#include "sorts/bubble_sort_system.h"

void ArraySystem::generateArray(uint16_t numElements) {

    sArray.clear();

    sArray.reserve(numElements);
    for (unsigned int i = 0; i < numElements; i++)
    {
        sArray.push_back(i);
    }
    mesh.generateMesh(sArray);
    sortSystem->reset();
}
std::mt19937 rng;
void ArraySystem::shuffle() {
    rng.seed(time(nullptr));

    std::uniform_int_distribution<unsigned int> gen(0, sArray.size() - 1);
    for (size_t i = 0; i < sArray.size(); i++)
    {
        unsigned int r = i;
        while (r == i)
            r = gen(rng);
        float temp = sArray[i];
        sArray[i] = sArray[r];
        sArray[r] = temp;
    }
    mesh.generateMesh(sArray);
    sortSystem->reset();

}
ComparisonData ArraySystem::sort() {

    ComparisonData it = sortSystem->iterate();
    if (it.status == SwapStatus::SWAP) {
        float temp = sArray[it.a];
        sArray[it.a] = sArray[it.b];
        sArray[it.b] = temp;
    }
    mesh.comparison(it);
    return it;

}