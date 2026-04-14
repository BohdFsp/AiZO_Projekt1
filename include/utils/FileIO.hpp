#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <fstream>
#include <iostream>
#include <string>

class FileIO {
public:
    template <typename Container>
    static bool loadFromFile(const std::string& filename, Container& array) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        size_t count;
        if (!(file >> count)) return false;

        using T = typename std::remove_reference<decltype(array[0])>::type;
        T value;

        for (size_t i = 0; i < count; ++i) {
            if (file >> value) array.push_back(value);
            else break;
        }
        file.close();
        return true;
    }

    template <typename Container>
    static bool saveToFile(const std::string& filename, Container& array) {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << array.size() << "\n";
        for (size_t i = 0; i < array.size(); ++i) {
            file << array[i] << "\n";
        }
        file.close();
        return true;
    }
};
#endif