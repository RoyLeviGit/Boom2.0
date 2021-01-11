//
// Created by tolev on 1/10/2021.
//

#ifndef BOOM2_0_DLL_H
#define BOOM2_0_DLL_H

#include "Node.h"

template <class T>
class DLL {
public:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;

    ~DLL() {
        while (head != nullptr) {
            auto node = head;
            head = head->next;
            delete node;
        }
    }

    /** Does not copy data */
    void insert(Node<T> *newNode) {
        if (head == nullptr) {
            head = newNode;
            tail = head;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        head->prev = nullptr;
    }

    /** Copies data */
    void insert(const T& data) {
        auto newNode = new Node<T>;
        newNode->data = data;
        insert(newNode);
    }

    /** Does not delete node */
    void pop(Node<T>* node) {
        if (node == nullptr) {
            return;
        }

        if (head == tail) {
            head = tail = nullptr;
            node->next = node->prev = nullptr;
            return;
        }
        else if (node == head) {
            head = node->next;
            head->prev = nullptr;
        }
        else if (node == tail) {
            tail = node->prev;
            tail->next = nullptr;
        }
        else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        node->next = node->prev = nullptr;
    }

    /** Deletes node */
    void remove(Node<T>* node) {
        pop(node);
        delete node;
    }
};

#endif //BOOM2_0_DLL_H
