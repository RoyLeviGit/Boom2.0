//
// Created by tolev on 1/10/2021.
//

#ifndef BOOM2_0_HASHTABLE_H
#define BOOM2_0_HASHTABLE_H

#include <cmath>
#include "DLL.h"
#include "Course.h"

#define MIN_CAPACITY 2
#define GROWTH_FACTOR 2

class HashTable {
    DLL<Course>* data = nullptr;
    int size = MIN_CAPACITY;
    int counter = 0;

    enum ResizeManual { Expand, Shrink };

    int hashMe(int key) const {
        double A = (sqrt(5)-1)/2;
        return floor(size * (key*A - floor(key*A)));
    }

    int newSize(enum ResizeManual manual) const {
        switch (manual) {
            case Expand: return size*GROWTH_FACTOR;
            case Shrink: return size/GROWTH_FACTOR;
            default: return 0; /** Should not get here */
        }
    }

    void resize(enum ResizeManual manual) {
        auto newData = new DLL<Course>[newSize(manual)];
        int oldSize = size;
        size = newSize(manual);
        for (int i = 0; i < oldSize; i++) {
            for (Node<Course>* courseNode = data[i].head; courseNode != nullptr; courseNode = courseNode->next) {
                int hashedKey = hashMe(courseNode->data.courseID);
                newData[hashedKey].insert(courseNode->data);
            }
        }
        delete [] data;
        data = newData;
    }

    Node<Course>* findNode(int key) {
        int hashedKey = hashMe(key);
        for (Node<Course>* courseNode = data[hashMe(key)].head; courseNode != nullptr; courseNode = courseNode->next) {
            if(courseNode->data.courseID == key) {
                return courseNode;
            }
        }
        return nullptr;
    }

public:
    explicit HashTable() : data(new DLL<Course>[INITIAL_CAPACITY]) {};

    ~HashTable() {
        delete [] data;
    }

    void insert(const Course& course) {
        int hashedKey = hashMe(course.courseID);
        data[hashedKey].insert(course);
        counter++;

        if (counter == size) {
            resize(Expand);
        }
    }

    void remove(const Course& course) {
        Node<Course>* courseNode = findNode(course.courseID);
        if (courseNode == nullptr) return;

        data[hashMe(course.courseID)].remove(courseNode);
        counter--;
        if(counter == size/2) {
            resize(Shrink);
        }
    }

    Course* find(int key) {
        Node<Course>* courseNode = findNode(key);
        return (courseNode != nullptr)? &courseNode->data : nullptr;
    }
};

#endif //BOOM2_0_HASHTABLE_H
