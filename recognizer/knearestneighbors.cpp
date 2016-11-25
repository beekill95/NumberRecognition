#include "knearestneighbors.h"

#include <algorithm>
#include <utility>
#include <map>
#include <cmath>
#include <climits>
#include <functional>

// helper classes //
typedef std::pair<double, std::vector<double>* > ElementType;
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
    double currentMaxDistance() const;
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

double MaxHeap::currentMaxDistance() const
{
    return heap[0].first;
}

bool MaxHeap::isEmpty() const
{
    return heap.size() == 0;
}

std::vector<double> getMajorityLabel(MaxHeap& heap)
{
    std::map<std::vector<double>, int> counter;

    while (!heap.isEmpty()) {
        ElementType element = heap.popHeap();

        if (counter.find(*element.second) == counter.end()) {
            counter[*element.second] = 1;
        } else {
            ++counter[*element.second];
        }
    }

    std::map<std::vector<double>, int>::const_iterator maxIter = counter.cbegin();
    auto it = maxIter; ++it;
    for (; it != counter.cend(); ++it) {
        if (it->second > maxIter->second)
            maxIter = it;
    }

    return maxIter->first;
}

double manhattanDistance(const std::vector<double>& first, const std::vector<double>& second, double currentMaxDistance, bool& abandon)
{
    double currentDistance = 0.0;
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

void KNearestNeighbors::train(const std::vector<std::vector<double> > &inputs, const std::vector<std::vector<double> > &outputs)
{
    this->inputs = inputs;
    this->outputs = outputs;
}

std::vector<double> KNearestNeighbors::predict(const std::vector<double> &input)
{
    MaxHeap maxHeap(k_neighbors);

    // calculate the distance between input and first k_neighbors
    double maxDistance = -1.0; // for early abandon
    bool abandon;
    for (int i = 0; i < k_neighbors; ++i) {
        double distance = manhattanDistance(input, inputs[i], std::numeric_limits<double>::max(), abandon);
        maxHeap.pushHeap(std::make_pair(distance, &outputs[i]));

        // update max distance
        if (distance > maxDistance)
            maxDistance = distance;
    }

    // calculate the distance between input and the rest
    for (size_t i = k_neighbors; i < inputs.size(); ++i) {
        double distance = manhattanDistance(input, inputs[i], maxDistance, abandon);

        if (!abandon) {
            maxHeap.removeHeadAndPush(std::make_pair(distance, &outputs[i]));
            maxDistance = maxHeap.currentMaxDistance();
        }
    }

    return getMajorityLabel(maxHeap);
}
