//
// Created by tolev on 06/01/2021.
//

#ifndef BOOM2_0_COURSE_H
#define BOOM2_0_COURSE_H

#define GROWTH_FACTOR 2
#define INITIAL_CAPACITY 4

#include "Vertex.h"
#include "Lecture.h"

class Course {
    int courseID;
    Vertex<Lecture>** lecturesVertices = nullptr;
    int numOfLectures = 0;
    int size = 0;

    void expand() {
        auto newData = new Vertex<Lecture>*[size*GROWTH_FACTOR];
        for (int i = 0; i < size; i++) {
            newData[i] = lecturesVertices[i];
        }
        size = size*GROWTH_FACTOR;

        delete [] lecturesVertices;
        lecturesVertices = newData;
    }

public:
    explicit Course(int courseID = 1)
            : courseID(courseID), lecturesVertices(new Vertex<Lecture>*[INITIAL_CAPACITY]) {};

    void addLecture() {
        lecturesVertices[numOfLectures] = nullptr;
        numOfLectures++;

        if (numOfLectures == size) {
            expand();
        }
    }

    Vertex<Lecture>* operator[](int index) {
        if (index < 0 || index >= numOfLectures) {
            return nullptr;
        }
        return lecturesVertices[index];
    }
};

#endif //BOOM2_0_COURSE_H
