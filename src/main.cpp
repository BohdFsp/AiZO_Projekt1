#include <iostream>
#include <chrono>
#include <algorithm>
#include "Parameters.h"
#include "structures/CustomArray.hpp"
#include "algorithms/BubbleSort.hpp"
#include "utils/FileIO.hpp"

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

    //1. ladowanie parametrow
    if (argc > 1) {
        Parameters::readParameters(argc - 1, argv + 1);
    } else {
        // Zabezpieczenie, gdyby ktoś uruchomił program całkowicie bez argumentów
        Parameters::readParameters(argc, argv);
    }



    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
        return 0;
    }

    // 2. Tryb pojedynczego pliku
    if (Parameters::runMode == Parameters::RunModes::singleFile) {
        CustomArray<int> arr;

        std::cout << "Wczytywanie z pliku: " << Parameters::inputFile << "...\n";
        if (!FileIO::loadFromFile(Parameters::inputFile, arr)) {
            return 1;
        }

        // std::sort demonstracja
        std::cout << "Rozpoczynam sortowanie babelkowe...\n";

        // 3. Mierzenie czasu w mikrosekundach (tylko algorytm) [cite: 29, 30]
        auto start_time = std::chrono::high_resolution_clock::now();

        bubbleSort(arr); // Używamy naszego algorytmu

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        // 4. Weryfikacja i wyniki
        if (isSorted(arr)) {
            std::cout << "Tablica posortowana poprawnie.\n";
        } else {
            std::cout << "Blad w sortowaniu!\n";
        }
        std::cout << "Czas sortowania: " << duration.count() << " us\n";

        // 5. Zapis wyników (jeśli podano plik wyjściowy)
        if (!Parameters::outputFile.empty()) {
            std::cout << "Zapisywanie wynikow do: " << Parameters::outputFile << "...\n";
            FileIO::saveToFile(Parameters::outputFile, arr);
        }
    }

    return 0;
}