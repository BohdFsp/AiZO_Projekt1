#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "structures/CustomArray.hpp"

class FileIO {
public:
    // Szablonowa funkcja do ładowania danych z pliku do tablicy
    template <typename T>
    static bool loadFromFile(const std::string& filename, CustomArray<T>& array) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Blad: Nie mozna otworzyc pliku do odczytu: " << filename << "\n";
            return false;
        }

        size_t count;
        if (!(file >> count)) return false; // Odczyt pierwszej linii (liczba elementow)

        T value;
        for (size_t i = 0; i < count; ++i) {
            if (file >> value) {
                array.push_back(value);
            } else {
                break; // Zabezpieczenie na wypadek mniejszej ilosci danych w pliku
            }
        }

        file.close();
        return true;
    }

    // Zapis posortowanych wartości do pliku analogicznie jak odczyt
    template <typename T>
    static bool saveToFile(const std::string& filename, CustomArray<T>& array) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Blad: Nie mozna otworzyc pliku do zapisu: " << filename << "\n";
            return false;
        }

        file << array.size() << "\n";
        for (size_t i = 0; i < array.size(); ++i) {
            file << array[i] << "\n";
        }

        file.close();
        return true;
    }
};

#endif