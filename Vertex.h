//
// Created by tolev on 06/01/2021.
//

#ifndef BOOM_VERTEX_H
#define BOOM_VERTEX_H

template <class T>
class Vertex {
public:
    Vertex<T>* parent = nullptr;
    Vertex<T>* left = nullptr;
    Vertex<T>* right = nullptr;
    T data;
    int height = 1;
    int rank = 1;
};

#endif //BOOM_VERTEX_H
