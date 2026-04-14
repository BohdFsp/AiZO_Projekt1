#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include "Parameters.h"

template <typename T, typename Container>
void shellSort(Container& arr) {
    size_t n = arr.size();
    if (n <= 1) return;

    size_t gap = 1;

    if (Parameters::shellParameter == Parameters::ShellParameters::option2) {
        while (gap < n / 3) gap = 3 * gap + 1;
    } else {
        gap = n / 2;
    }

    for (; gap > 0; gap = (Parameters::shellParameter == Parameters::ShellParameters::option2) ? gap / 3 : gap / 2) {
        for (size_t i = gap; i < n; i++) {
            T temp = arr[i];
            size_t j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
        if (Parameters::shellParameter != Parameters::ShellParameters::option2 && gap == 1) break;
    }
}
#endif