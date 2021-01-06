//
// Created by tolev on 06/01/2021.
//

#ifndef BOOM_AVL_H
#define BOOM_AVL_H

#include <iostream>
#include "Vertex.h"

template <class T>
class AVL {
private:
    Vertex<T> *root = nullptr;

    // Post order destruction
    void recursiveDestructor(Vertex<T> *vertex) {
        if (vertex == nullptr) {
            return;
        }
        recursiveDestructor(vertex->right);
        recursiveDestructor(vertex->left);
        delete vertex;
    }

    // returns Height of Vertex
    int calculateHeight(Vertex<T> *vertex){
        if(vertex->left && vertex->right) {
            if (vertex->left->height < vertex->right->height)
                return vertex->right->height + 1;
            else return vertex->left->height + 1;
        }
        else if(vertex->left && vertex->right == nullptr)
            return vertex->left->height + 1;
        else if(vertex->left == nullptr && vertex->right)
            return vertex->right->height + 1;
        return 1;
    }

    // returns Rank of Vertex
    int calculateRank(Vertex<T> *vertex) {
        if(vertex->left && vertex->right) {
            return vertex->right->rank + vertex->left->rank + 1;
        }
        else if(vertex->left && vertex->right == nullptr)
            return vertex->left->rank + 1;
        else if(vertex->left == nullptr && vertex->right)
            return vertex->right->rank + 1;
        return 1;
    }

    // returns Balance Factor of Vertex
    int balanceFactor(Vertex<T> *vertex){
        if(vertex->left && vertex->right){
            return vertex->left->height - vertex->right->height;
        }
        else if(vertex->left && vertex->right == nullptr){
            return vertex->left->height;
        }
        else if(vertex->left== nullptr && vertex->right ){
            return -vertex->right->height;
        }
        return 0;
    }

    /**
     * rolls function
     * @param vertex where balance was bad
     * @return the new vertex in place of the vertex given
     */
    Vertex<T>* rotateLL(Vertex<T> *vertex) {
        Vertex<T> *b = vertex, *a = vertex->left;
        if (b == root) root = a;

        if (b->parent != nullptr) {
            if (b->parent->left == b)
                b->parent->left = a;
            else
                b->parent->right = a;
        }
        a->parent = b->parent;
        b->parent = a;
        if (a->right != nullptr) a->right->parent = b;

        b->left = a->right;
        a->right = b;

        b->height = calculateHeight(b);
        a->height = calculateHeight(a);

        b->rank = calculateRank(b);
        a->rank = calculateRank(a);
        return a;
    }

    Vertex<T>* rotateRR(Vertex<T> *vertex) {
        Vertex<T> *b = vertex, *a = vertex->right;
        if (b == root) root = a;

        if (b->parent != nullptr) {
            if (b->parent->left == b)
                b->parent->left = a;
            else
                b->parent->right = a;
        }
        a->parent = b->parent;
        b->parent = a;
        if (a->left != nullptr) a->left->parent = b;

        b->right = a->left;
        a->left = b;

        b->height = calculateHeight(b);
        a->height = calculateHeight(a);

        b->rank = calculateRank(b);
        a->rank = calculateRank(a);
        return a;
    }

    Vertex<T>* rotateLR(Vertex<T> *vertex) {
        Vertex<T> *c = vertex, *a = vertex->left, *b = vertex->left->right;
        if (c == root) root = b;

        if (c->parent != nullptr) {
            if (c->parent->left == c)
                c->parent->left = b;
            else
                c->parent->right = b;
        }
        b->parent = c->parent;
        c->parent = b;
        a->parent = b;
        if (b->left != nullptr) b->left->parent = a;
        if (b->right != nullptr) b->right->parent = c;

        c->left = b->right;
        a->right = b->left;
        b->left = a;
        b->right = c;

        a->height = calculateHeight(a);
        c->height = calculateHeight(c);
        b->height = calculateHeight(b);

        a->rank = calculateRank(a);
        c->rank = calculateRank(c);
        b->rank = calculateRank(b);
        return b;
    }

    Vertex<T>* rotateRL(Vertex<T> *vertex) {
        Vertex<T> *c = vertex, *a = vertex->right, *b = vertex->right->left;
        if (c == root) root = b;

        if (c->parent != nullptr) {
            if (c->parent->left == c)
                c->parent->left = b;
            else
                c->parent->right = b;
        }
        b->parent = c->parent;
        c->parent = b;
        a->parent = b;
        if (b->right != nullptr) b->right->parent = a;
        if (b->left != nullptr) b->left->parent = c;

        c->right = b->left;
        a->left = b->right;
        b->right = a;
        b->left = c;

        a->height = calculateHeight(a);
        c->height = calculateHeight(c);
        b->height = calculateHeight(b);

        a->rank = calculateRank(a);
        c->rank = calculateRank(c);
        b->rank = calculateRank(b);
        return b;
    }

    Vertex<T>* predecessor(Vertex<T>* vertex){
        while(vertex->right != nullptr) vertex = vertex->right;
        return vertex;
    }
    Vertex<T>* postdecessor(Vertex<T>* vertex){
        while(vertex->left != nullptr) vertex = vertex->left;
        return vertex;
    }

    /**
     * switches between two vertices without changing their data
     */
    Vertex<T>* switchVertices(Vertex<T>* vertex, Vertex<T>* toVertex) {
        Vertex<T> temp;
        if (vertex == root) root = toVertex;

        if (vertex->parent != nullptr) {
            if (vertex->parent->left == vertex)
                vertex->parent->left = toVertex;
            else
                vertex->parent->right = toVertex;
        }
        if (vertex->left != nullptr && vertex->left != toVertex) vertex->left->parent = toVertex;
        if (vertex->right != nullptr && vertex->right != toVertex) vertex->right->parent = toVertex;

        if (toVertex->parent != nullptr && toVertex->parent != vertex) {
            if (toVertex->parent->left == toVertex)
                toVertex->parent->left = vertex;
            else
                toVertex->parent->right = vertex;
        }
        if (toVertex->left != nullptr) toVertex->left->parent = vertex;
        if (toVertex->right != nullptr) toVertex->right->parent = vertex;

        temp.left = toVertex->left;
        temp.right = toVertex->right;
        temp.parent = (toVertex->parent == vertex) ? toVertex : toVertex->parent;
        temp.height = toVertex->height;
        temp.rank = toVertex->rank;

        toVertex->left = (vertex->left == toVertex) ? vertex : vertex->left;
        toVertex->right = (vertex->right == toVertex) ? vertex : vertex->right;
        toVertex->parent = vertex->parent;
        toVertex->height = vertex->height;
        toVertex->rank = vertex->rank;

        vertex->left = temp.left;
        vertex->right = temp.right;
        vertex->parent = temp.parent;
        vertex->height = temp.height;
        vertex->rank = temp.rank;

        return toVertex;
    }

    /**
     * insert Function
     * @param vertex from which we start to search the right place for the new data.
     * @param data to insert to tree.
     * @param exist *bool to indicate if the data already exist in the tree
     * @return the root (should be ignored)
     */
    Vertex<T>* insert(const T& data, Vertex<T> *vertex, bool* exists = nullptr, Vertex<T>* parent = nullptr, bool justLeft = true) {
        if(vertex==nullptr){
            vertex = new Vertex<T>;
            vertex->data = data;
            vertex->left = vertex->right = nullptr;
            vertex->parent = parent;
            vertex->height = 1;
            vertex->rank = 1;
            if (root == nullptr)
                this->root = vertex;
            if (justLeft)
                this->pfh = vertex;
            if (exists != nullptr) *exists = false;
            return vertex;
        } else {
            if(data < vertex->data)
                vertex->left = insert(data, vertex->left, exists, vertex, justLeft);
            else if(data > vertex->data)
                vertex->right = insert(data, vertex->right, exists, vertex, false);
            else
            if (exists != nullptr) *exists = true;
        }
        vertex->height = calculateHeight(vertex);
        vertex->rank = calculateRank(vertex); // update rank of vertices in path

        if(balanceFactor(vertex)==2 && balanceFactor(vertex->left)>=0)
            vertex = rotateLL(vertex);
        else if(balanceFactor(vertex)==2 && balanceFactor(vertex->left)==-1)
            vertex = rotateLR(vertex);
        else if(balanceFactor(vertex)==-2 && balanceFactor(vertex->right)<=0)
            vertex = rotateRR(vertex);
        else if(balanceFactor(vertex)==-2 && balanceFactor(vertex->right)==1)
            vertex = rotateRL(vertex);

        return vertex;
    }

    /**
     * remove Function
     * @param vertex from which we start to search the right place for the  data.
     * @param data to remove from tree.
     * @param exist *bool to indicate if the data was already exist in the tree
     * @return the root (should be ignored)
     */
    Vertex<T>* remove(const T& data, Vertex<T> *vertex, bool* exists = nullptr, bool justLeft = true) {
        if (vertex == nullptr) {
            if (exists != nullptr) *exists = false;
            return nullptr;
        }
        if(vertex->left == nullptr && vertex->right == nullptr) {
            if (vertex->data != data) {
                if (exists != nullptr) *exists = false;
                return vertex;
            }
            if(vertex==this->root)
                this->root = nullptr;
            if (justLeft)
                this->pfh = vertex->parent;
            delete vertex;
            if (exists != nullptr) *exists = true;
            return nullptr;
        }

        if(vertex->data < data){
            vertex->right = remove(data, vertex->right, exists, false);
        }
        else if(vertex->data > data){
            vertex->left = remove(data, vertex->left, exists, justLeft);
        } else {
            if (vertex->left != nullptr) {
                Vertex<T>* preVertex = predecessor(vertex->left);
                vertex = switchVertices(vertex, preVertex);
                vertex->left = remove(data, vertex->left, exists, justLeft);
            } else {
                Vertex<T>* postVertex = postdecessor(vertex->right); // vertex->right != nullptr
                vertex = switchVertices(vertex, postVertex);
                vertex->right = remove(data, vertex->right, exists, false);
            }
        }
        vertex->height = calculateHeight(vertex);
        vertex->rank = calculateRank(vertex); // update rank of vertices in path

        if(balanceFactor(vertex)==2 && balanceFactor(vertex->left)>=0)
            vertex = rotateLL(vertex);
        else if(balanceFactor(vertex)==2 && balanceFactor(vertex->left)==-1)
            vertex = rotateLR(vertex);
        else if(balanceFactor(vertex)==-2 && balanceFactor(vertex->right)<=0)
            vertex = rotateRR(vertex);
        else if(balanceFactor(vertex)==-2 && balanceFactor(vertex->right)==1)
            vertex = rotateRL(vertex);

        return vertex;
    }

    /**
     * GetRank Function
     * @param vertex the root vertex from which we start to search.
     * @param i the index to find. i>=1
     * @return the data, nullptr if no such data exists
     */
    const T* getRank(int i, Vertex<T> *vertex) { //TODO: const?
        if (vertex == nullptr)
            return nullptr;
        else if (calculateRank(vertex->left) >= i) // should i go left?
            return getRank(i, vertex->left);
        else if (calculateRank(vertex->left)+1 < i) // should i go right?
            return getRank(i-calculateRank(vertex->left)-1, vertex->right);
        return vertex->data;
    }

public:

    ~AVL() {
        recursiveDestructor(root);
    }

    // insert shell
    Vertex<T>* insert(const T& data, bool* exists = nullptr) {
        return insert(data, root, exists, nullptr, true);
    }

    // remove shell
    Vertex<T>* remove(const T& data, bool* exists = nullptr) {
        return remove(data, root, exists, true);
    }

    // remove shell
    const T* getRank(int i) {
        return getRank(i, root);
    }
};

#endif //BOOM_AVL_H
