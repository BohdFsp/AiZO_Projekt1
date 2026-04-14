#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <utility>
#include <random>
#include "Parameters.h"

template <typename T, typename Container>
int partition(Container& arr, int low, int high) {
    int pIdx = high;

    // Wybór pivota wg parametrów z biblioteki
    if (Parameters::pivot == Parameters::Pivots::left) pIdx = low;
    else if (Parameters::pivot == Parameters::Pivots::middle) pIdx = low + (high - low) / 2;
    else if (Parameters::pivot == Parameters::Pivots::random) {
        pIdx = low + (rand() % (high - low + 1));
    }

    std::swap(arr[pIdx], arr[high]);
    T pivotValue = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivotValue) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T, typename Container>
void quickSort(Container& arr, int low, int high) {
    if (low < high) {
        int pi = partition<T>(arr, low, high);
        quickSort<T>(arr, low, pi - 1);
        quickSort<T>(arr, pi + 1, high);
    }
}
#endif