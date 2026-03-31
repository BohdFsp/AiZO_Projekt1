#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include <utility> // dla std::swap
#include "structures/CustomArray.hpp"

template <typename T>
void bubbleSort(CustomArray<T>& arr) {
    size_t n = arr.size();
    if (n == 0) return;

    bool swapped;
    for (size_t i = 0; i < n - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // jeśli w danej iteracji nie było zamian, tablica jest posortowana
        if (!swapped) break;
    }
}

#endif