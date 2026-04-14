#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include <ctime>
#include <iomanip>
#include <string>
#include <type_traits>

#include "Parameters.h"
#include "CustomArray.hpp"
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"
#include "Queue.hpp"
#include "BinaryTree.hpp"
#include "BucketSort.hpp"
#include "QuickSort.hpp"
#include "ShellSort.hpp"
#include "FileIO.hpp"

// =========================================================================
// WERYFIKACJA
// =========================================================================
template <typename Container>
bool verifySort(Container& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

// =========================================================================
// EGZEKUTOR ALGORYTMÓW
// =========================================================================
template <typename T, typename Container>
// Globalny menedżer uruchamiający wybrany algorytm
void executeSort(Container& arr) {
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        // Kompilator wygeneruje ten kod tylko dla typów liczbowych
        // string ta część kodu zostanie zignorowana podczas kompilacji
        if constexpr (std::is_arithmetic_v<T>) {
            bucketSort<T, Container>(arr);
        } else {
            std::cerr << "Blad: Bucket Sort wymaga danych liczbowych. Uzyj Quick/Shell Sort dla std::string.\n";
        }
    }
    else if (Parameters::algorithm == Parameters::Algorithms::quick) {
        quickSort<T>(arr, 0, arr.size() - 1);
    }
    else if (Parameters::algorithm == Parameters::Algorithms::shell) {
        shellSort<T>(arr);
    }
}

// =========================================================================
// ZAPIS WYNIKÓW
// =========================================================================
void logResult(long long min, long long max, long long avg) {
    std::ofstream file(Parameters::resultsFile, std::ios::app);
    if (file.is_open()) {
        std::time_t now = std::time(nullptr);
        file << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << ","
             << (int)Parameters::algorithm << "," << (int)Parameters::structure << ","
             << (int)Parameters::dataType << "," << Parameters::structureSize << ","
             << min << "," << max << "," << avg << "\n";
    }
}

// =========================================================================
// GENERATORY DANYCH
// =========================================================================
template <typename T> T generateRandomValue(std::mt19937& gen);

template <> int generateRandomValue<int>(std::mt19937& gen) {
    return std::uniform_int_distribution<int>(INT32_MIN, INT32_MAX)(gen);
}

template <> unsigned int generateRandomValue<unsigned int>(std::mt19937& gen) {
    return std::uniform_int_distribution<unsigned int>(0, UINT32_MAX)(gen);
}

template <> float generateRandomValue<float>(std::mt19937& gen) {
    // Generowanie z pełnego zakresu dla float
    return std::uniform_real_distribution<float>(-1000000.0f, 1000000.0f)(gen);
}

template <> std::string generateRandomValue<std::string>(std::mt19937& gen) {
    // Łańcuch znaków "printables" o losowej długości
    std::uniform_int_distribution<int> lengthDist(5, 15);
    std::uniform_int_distribution<int> charDist(32, 126); // Kody ASCII znaków drukowalnych
    int len = lengthDist(gen);
    std::string result = "";
    for(int i = 0; i < len; ++i) result += static_cast<char>(charDist(gen));
    return result;
}

// =========================================================================
// GŁÓWNY PROGRAM URUCHOMIENIOWY DLA DOWOLNEGO TYPU I KONTENERA
// =========================================================================
template <typename T, typename Container>
void runProcess() {
    if (Parameters::runMode == Parameters::RunModes::singleFile) {
        Container arr;
        if (!FileIO::loadFromFile(Parameters::inputFile, arr)) {
            std::cerr << "Blad wczytywania.\n"; return;
        }

        auto start = std::chrono::high_resolution_clock::now();
        executeSort<T>(arr);
        auto end = std::chrono::high_resolution_clock::now();

        if (verifySort(arr)) {
            std::cout << "Czas: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
        }
        if (!Parameters::outputFile.empty()) FileIO::saveToFile(Parameters::outputFile, arr);
    }
    else if (Parameters::runMode == Parameters::RunModes::benchmark) {
        long long total = 0, minT = 1e18, maxT = 0;
        std::mt19937 gen(time(0));

        for (int i = 0; i < Parameters::iterations; ++i) {
            Container data;
            // Generowanie danych odpowiedniego typu (poza czasem)
            for (int j = 0; j < Parameters::structureSize; ++j) {
                data.push_back(generateRandomValue<T>(gen));
            }

            auto start = std::chrono::high_resolution_clock::now();
            executeSort<T>(data);
            auto end = std::chrono::high_resolution_clock::now();

            long long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            if (!verifySort(data)) { std::cerr << "Blad w iteracji " << i << "\n"; return; }

            total += duration;
            if (duration < minT) minT = duration;
            if (duration > maxT) maxT = duration;
        }

        logResult(minT, maxT, total / Parameters::iterations);
        std::cout << "Zapisano wyniki.\n";
    }
}

// =========================================================================
// ROUTER TYPÓW
// =========================================================================
template <template<typename> class ContainerType>
void routeDataType() {
    if (Parameters::dataType == Parameters::DataTypes::typeInt) {
        runProcess<int, ContainerType<int>>();
    }
    else if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
        runProcess<float, ContainerType<float>>();
    }
    else if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
        runProcess<unsigned int, ContainerType<unsigned int>>();
    }
    else if (Parameters::dataType == Parameters::DataTypes::typeString) {
        runProcess<std::string, ContainerType<std::string>>();
    }
    else {
        std::cerr << "Ten typ danych nie jest zaimplementowany do badania.\n";
    }
}

// =========================================================================
// MAIN
// =========================================================================
int main(int argc, char* argv[]) {
    if (argc > 1) Parameters::readParameters(argc - 1, argv + 1);
    else { Parameters::help(); return 0; }

    if (Parameters::runMode == Parameters::RunModes::help) { Parameters::help(); return 0; }

    // Wybór struktury (Obsługa 5 struktur)
    if (Parameters::structure == Parameters::Structures::array) routeDataType<CustomArray>();
    else if (Parameters::structure == Parameters::Structures::singleList) routeDataType<SinglyLinkedList>();
    else if (Parameters::structure == Parameters::Structures::doubleList) routeDataType<DoublyLinkedList>();
    else if (Parameters::structure == Parameters::Structures::queue) routeDataType<Queue>();
    else if (Parameters::structure == Parameters::Structures::binaryTree) routeDataType<BinaryTree>();
    else std::cerr << "Nieznana struktura.\n";

    return 0;
}