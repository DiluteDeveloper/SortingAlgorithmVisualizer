#include "array/array_system.h"

#include <random>
#include "sorts/bubble_sort_system.h"


std::mt19937 rng((unsigned int)time(nullptr));
ArraySystem::ArraySystem(unsigned int numElements, unsigned int heightComplexity) {

    std::uniform_int_distribution<unsigned int> gen(1, heightComplexity); // uniform, unbiased
    for (size_t i = 0; i < numElements; i++)
    {

        unsigned int r = gen(rng);
        arrayObj.push_back(r);
    }

    ar = std::make_unique<ArrayRenderer>(arrayObj, heightComplexity);
    sortAlg = std::make_unique<BubbleSortSystem>(arrayObj);
}
IterInfo ArraySystem::sort() {
    IterInfo it(0,0);

    it = sortAlg->iterate();
    if (it)
        ar->swap(it.swapFst, it.swapSnd);



    return it;

}
void ArraySystem::render() {
    ar->render();
}
void ArraySystem::updateMesh() {
    ar->updateMesh();
}