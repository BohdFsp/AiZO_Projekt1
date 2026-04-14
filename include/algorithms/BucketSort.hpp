#ifndef BUCKET_SORT_HPP
#define BUCKET_SORT_HPP

#include "CustomArray.hpp"

// Pomocnicze sortowanie kubełka (Insertion Sort)
template <typename T, typename Container>
void bucketInsertionSort(Container& arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        T key = arr[i];
        int j = (int)i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Główny Bucket Sort
template <typename T, typename Container>
void bucketSort(Container& arr) {
    size_t n = arr.size();
    if (n <= 1) return;

    // Szukanie min i max do wyznaczenia zakresu kubełków
    T min_val = arr[0];
    T max_val = arr[0];
    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    if (min_val == max_val) return;

    // Tworzenie kubełków
    size_t bucket_count = n;
    CustomArray<CustomArray<T>> buckets;
    for (size_t i = 0; i < bucket_count; ++i) {
        buckets.push_back(CustomArray<T>());
    }

    // Rozdzielanie do kubełków
    double range = (double)max_val - (double)min_val;
    for (size_t i = 0; i < n; ++i) {
        int b_idx = (int)(( (double)arr[i] - (double)min_val ) / range * (bucket_count - 1));
        buckets[b_idx].push_back(arr[i]);
    }

    // Sortowanie kubełków i scalanie
    size_t idx = 0;
    for (size_t i = 0; i < bucket_count; ++i) {
        if (buckets[i].size() > 0) {
            bucketInsertionSort<T, CustomArray<T>>(buckets[i]);
            for (size_t j = 0; j < buckets[i].size(); ++j) {
                arr[idx++] = buckets[i][j];
            }
        }
    }
}

#endif