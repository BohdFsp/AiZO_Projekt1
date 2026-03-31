#ifndef CUSTOM_ARRAY_HPP
#define CUSTOM_ARRAY_HPP

#include <cstddef>

template <typename T>
class CustomArray {
private:
    T* data;
    size_t current_size;
    size_t current_capacity;

    void reallocate(size_t new_capacity) {
        // Ręczne alokowanie pamięci
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < current_size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data; // Ręczne zwalnianie
        data = new_data;
        current_capacity = new_capacity;
    }

public:
    CustomArray() : data(nullptr), current_size(0), current_capacity(0) {}

    ~CustomArray() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (current_size == current_capacity) {
            reallocate(current_capacity == 0 ? 1 : current_capacity * 2);
        }
        data[current_size++] = value;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    size_t size() const { return current_size; }
};

#endif