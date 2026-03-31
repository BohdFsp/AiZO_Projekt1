#include <iostream>
#include <chrono>
#include "Parameters.h" // Dołączenie biblioteki prowadzącego
#include "structures/CustomArray.hpp"

//funkcja sprawdzająca, czy elementy są uporządkowane rosnąco
template <typename T>
bool isSorted(CustomArray<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    // Odczyt parametrów z wykorzystaniem udostępnionej biblioteki
    Parameters::readParameters(argc, argv);

    // Wymagany tryb pomocy
    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
        return 0;
    }

    // podstawowy element badany
    CustomArray<int> arr;
    arr.push_back(10);
    arr.push_back(-5);
    arr.push_back(42);
    arr.push_back(0);

    // Mierzenie czasu w mikrosekundach
    auto start_time = std::chrono::high_resolution_clock::now();

    // jakiś algorytm

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);


    if (isSorted(arr)) {
        std::cout << "Tablica posortowana poprawnie.\n";
    } else {
        std::cout << "Blad w sortowaniu!\n";
    }

    std::cout << "Czas sortowania: " << duration.count() << " us\n";

    return 0;
}