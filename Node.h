//
// Created by tolev on 1/10/2021.
//

#ifndef BOOM2_0_NODE_H
#define BOOM2_0_NODE_H

template <class T>
class Node {
public:
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;
    T data;
};

#endif //BOOM2_0_NODE_H
