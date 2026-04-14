#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node *head, *tail;
    size_t _size;

public:
    Queue() : head(nullptr), tail(nullptr), _size(0) {}
    ~Queue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(T val) {
        Node* newNode = new Node(val);
        if (!tail) { head = tail = newNode; }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        _size++;
    }

    // Wolny dostęp sekwencyjny
    T& operator[](size_t index) {
        Node* temp = head;
        for (size_t i = 0; i < index; ++i) temp = temp->next;
        return temp->data;
    }

    size_t size() const { return _size; }
};
#endif