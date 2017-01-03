#include "knearestneighbors.h"

#include <algorithm>
#include <utility>
#include <map>
#include <cmath>
#include <climits>
#include <functional>

// helper classes //
typedef std::pair<val_type, const std::vector<val_type>* > ElementType;
typedef std::vector<ElementType> HeapType;

class MaxHeap
{
private:
    HeapType heap;
    std::function<bool(const ElementType&, const ElementType&)> compareFunction;

public:
    MaxHeap(int size);
    ~MaxHeap();

    void pushHeap(const ElementType& element);
    ElementType popHeap();

    ElementType removeHeadAndPush(const ElementType& element);
    val_type currentMaxDistance() const;
    bool isEmpty() const;
};

MaxHeap::MaxHeap(int size)
{
    heap.reserve(size);

    compareFunction = [](const ElementType& first, const ElementType& second) {
        return first.first < second.first;
    };
}

MaxHeap::~MaxHeap()
{
    heap.clear();
}

void MaxHeap::pushHeap(const ElementType &element)
{
    heap.push_back(element);
    std::push_heap(heap.begin(), heap.end(), compareFunction);
}

ElementType MaxHeap::popHeap()
{
    std::pop_heap(heap.begin(), heap.end(), compareFunction);
    ElementType element = heap.back();
    heap.pop_back();
    return element;
}

ElementType MaxHeap::removeHeadAndPush(const ElementType &element)
{
    ElementType popElement = popHeap();
    pushHeap(element);
    return popElement;
}

val_type MaxHeap::currentMaxDistance() const
{
    return heap[0].first;
}

bool MaxHeap::isEmpty() const
{
    return heap.size() == 0;
}

std::vector<val_type> getMajorityLabel(MaxHeap& heap)
{
    std::map<std::vector<val_type>, int> counter;

    while (!heap.isEmpty()) {
        ElementType element = heap.popHeap();

        if (counter.find(*element.second) == counter.end()) {
            counter[*element.second] = 1;
        } else {
            ++counter[*element.second];
        }
    }

    std::map<std::vector<val_type>, int>::const_iterator maxIter = counter.cbegin();
    auto it = maxIter; ++it;
    for (; it != counter.cend(); ++it) {
        if (it->second > maxIter->second)
            maxIter = it;
    }

    return maxIter->first;
}

val_type manhattanDistance(const std::vector<val_type>& first, const std::vector<val_type>& second, val_type currentMaxDistance, bool& abandon)
{
    val_type currentDistance = 0.0;
    abandon = false;
    for (size_t i = 0; i < first.size(); ++i) {
        currentDistance += fabs(first[i] - second[i]);

        if (currentDistance > currentMaxDistance) {
            abandon = true;
            break;
        }
    }

    return currentDistance;
}

///////////////////////

KNearestNeighbors::KNearestNeighbors(int k_neighbors)
    : k_neighbors(k_neighbors)
{ }

KNearestNeighbors::~KNearestNeighbors()
{
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        inputs[i].clear();
        outputs[i].clear();
    }

    inputs.clear();
    outputs.clear();
}

void KNearestNeighbors::train(const std::vector<std::vector<val_type> > &inputs, const std::vector<std::vector<val_type> > &outputs)
{
    this->inputs = inputs;
    this->outputs = outputs;
}

std::vector<val_type> KNearestNeighbors::predict(const std::vector<val_type> &input, bool verbose) const
{
    MaxHeap maxHeap(k_neighbors);

    // calculate the distance between input and first k_neighbors
    val_type maxDistance = -1.0; // for early abandon
    bool abandon;
    for (int i = 0; i < k_neighbors; ++i) {
        val_type distance = manhattanDistance(input, inputs[i], std::numeric_limits<val_type>::max(), abandon);
        maxHeap.pushHeap(std::make_pair(distance, &outputs.at(i)));

        // update max distance
        if (distance > maxDistance)
            maxDistance = distance;
    }

    // calculate the distance between input and the rest
    for (size_t i = k_neighbors; i < inputs.size(); ++i) {
        val_type distance = manhattanDistance(input, inputs[i], maxDistance, abandon);

        if (!abandon) {
            maxHeap.removeHeadAndPush(std::make_pair(distance, &outputs.at(i)));
            maxDistance = maxHeap.currentMaxDistance();
        }
    }

    return getMajorityLabel(maxHeap);
}
