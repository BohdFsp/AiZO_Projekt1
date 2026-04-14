#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <cstddef>

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* head;
    size_t _size;

public:
    SinglyLinkedList() : head(nullptr), _size(0) {}
    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(T val) {
        Node* newNode = new Node(val);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        _size++;
    }

    T& operator[](size_t index) {
        Node* temp = head;
        for (size_t i = 0; i < index; ++i) temp = temp->next;
        return temp->data;
    }

    size_t size() const { return _size; }
};
#endif