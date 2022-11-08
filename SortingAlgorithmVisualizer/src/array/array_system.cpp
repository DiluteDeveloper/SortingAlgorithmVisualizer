#include "array/array_system.h"

#include "sorts/bubble_sort_system.h"
#include "random/random.h"

ArraySystem::ArraySystem(uint16_t numElements, uint16_t heightComplexity) {

    std::uniform_int_distribution<uint16_t> gen(1, heightComplexity); // uniform, unbiased
    for (size_t i = 0; i < numElements; i++)
    {

        uint16_t r = gen(rng);
        arrayObj.push_back(r);
    }

    aRenderer = std::make_unique<ArrayRenderer>(arrayObj, heightComplexity);
    sortSystem = std::make_unique<BubbleSortSystem>(arrayObj);
}
OperationData ArraySystem::sort() {

    OperationData it;
    if (!aSorted) { // if not sorted
        it = sortSystem->iterate();
        if (!(aSorted = static_cast<bool>(it))) {
            aRenderer->swap(it.swapFst, it.swapSnd);
        }
    }

    return it;

}
void ArraySystem::render() {
    aRenderer->render();
}
void ArraySystem::updateMesh() {
    aRenderer->updateMesh();
}