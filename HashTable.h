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

    typedef enum ResizeManual { Expand, Shrink } ResizeManual;

    /**
     * Hashing function for the hash table, using 0<a<1 method, O(1)
     * @param key the key index of the object to hash
     * @return index for key in the range: 0-(size-1)
     */
    int hashMe(int key) const {
        double A = (sqrt(5)-1)/2;
        return floor(size * (key*A - floor(key*A)));
    }
    /**
     * computes the new size fot the resize function of hash table dynamic array
     * @param manual, enum that represents the type of resizing
     *
     */
    int newSize(ResizeManual manual) const {
        switch (manual) {
            case Expand: return size*GROWTH_FACTOR;
            case Shrink: return size/GROWTH_FACTOR;
            default: return 0; /** Should not get here */
        }
    }
    /**
     * Resize the hash table dynamic array
     * @param manual, enum that represents the type of resizing
     */
    void resize(ResizeManual manual) {
        auto newData = new DLL<Course>[newSize(manual)];
        int oldSize = size;
        size = newSize(manual);
        for (int i = 0; i < oldSize; i++) {
            for (auto node = data[i].head; node != nullptr; node = data[i].head) {
                int hashedKey = hashMe(data[i].head->data.courseID);
                data[i].pop(node); /** Pops head node from DLL. must be done before insertion */
                newData[hashedKey].insert(node); /** Copies Node and doesn't call course copy constructor */
            }
        }
        delete [] data;
        data = newData;
    }
    /**
     *Find Node<course> using a given key
     * @param key of certain course
     * @return pointer for the Node<course> if found a matching one, else nullptr
     */
    Node<Course>* findNode(int key) {
        int hashedKey = hashMe(key);
        for (Node<Course>* courseNode = data[hashedKey].head; courseNode != nullptr; courseNode = courseNode->next) {
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
    /**
     *Insert the given course from the hash table
     * @param refrence of certain course
     */
    void insert(const Course& course) {
        int hashedKey = hashMe(course.courseID);
        data[hashedKey].insert(course);
        counter++;

        if (counter == size) {
            resize(Expand);
        }
    }
    /**
     *Remove the given course from the hash table
     * @param refrence of certain course
     */
    void remove(const Course& course) {
        Node<Course>* courseNode = findNode(course.courseID);
        if (courseNode == nullptr) return;

        data[hashMe(course.courseID)].remove(courseNode);
        counter--;

        if(counter == size/2) {
            resize(Shrink);
        }
    }
    /**
     *Find the given course from the hash table
     * @param key of certain course
     * @return pointer for the course, else nullptr
     */
    Course* find(int key) {
        Node<Course>* courseNode = findNode(key);
        return (courseNode != nullptr)? &courseNode->data : nullptr;
    }
};

#endif //BOOM2_0_HASHTABLE_H
