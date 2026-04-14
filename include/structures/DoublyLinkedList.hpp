#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <cstddef>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node *next, *prev;
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };
    Node *head, *tail;
    size_t _size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), _size(0) {}
    ~DoublyLinkedList() {
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
            newNode->prev = tail;
            tail = newNode;
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