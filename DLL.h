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

    void insert(const T& data) {
        if (head == nullptr) {
            head = new Node<T>;
            head->data = data;
            tail = head;
            return;
        }
        auto newNode = new Node<T>;
        newNode->data = data;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void remove(Node<T>* node) {
        if (node == nullptr) {
            return;
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }
        else if (node == head) {
            head = node->next;
        }
        else if (node == tail) {
            tail = node->prev;
        }
        else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        delete node;
    }
};

#endif //BOOM2_0_DLL_H
