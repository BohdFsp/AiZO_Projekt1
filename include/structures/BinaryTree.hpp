#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <cstddef>
#include "CustomArray.hpp"

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node *left, *right;
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };
    Node* root;
    size_t _size;

    // Używamy naszej CustomArray jako bufora, żeby algorytmy sortujące miały do tego dostęp po indeksie
    CustomArray<T*> node_pointers;

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr), _size(0) {}
    ~BinaryTree() { destroyTree(root); }

    // Proste wstawianie (bez balansowania)
    void push_back(T val) {
        Node* newNode = new Node(val);
        node_pointers.push_back(&newNode->data);

        if (!root) { root = newNode; _size++; return; }

        Node* current = root;
        while (true) {
            if (val < current->data) {
                if (!current->left) { current->left = newNode; break; }
                current = current->left;
            } else {
                if (!current->right) { current->right = newNode; break; }
                current = current->right;
            }
        }
        _size++;
    }

    T& operator[](size_t index) { return *(node_pointers[index]); }
    size_t size() const { return _size; }
};
#endif