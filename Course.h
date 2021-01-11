//
// Created by tolev on 06/01/2021.
//

#ifndef BOOM2_0_COURSE_H
#define BOOM2_0_COURSE_H

#define GROWTH_FACTOR 2
#define INITIAL_CAPACITY 2

#include "Lecture.h"

class Course {
    int size = INITIAL_CAPACITY;

    void expand() {
        auto newData = new Lecture*[size*GROWTH_FACTOR];
        for (int i = 0; i < size*GROWTH_FACTOR; i++) {
            newData[i] = (i < size) ? lectures[i] : nullptr;
        }
        size = size*GROWTH_FACTOR;

        delete [] lectures;
        lectures = newData;
    }

public:
    int courseID;
    int numOfLectures = 0;
    Lecture** lectures = nullptr; /** DynamicArray of pointers to lecture vertices */

    explicit Course(int courseID = 0) : courseID(courseID), lectures(new Lecture*[INITIAL_CAPACITY]) {
        for (int i = 0; i < INITIAL_CAPACITY; i++) {
            lectures[i] = nullptr;
        }
    };

    ~Course() {
        delete [] lectures; //TODO: check if entered when hashTable gets deleted
    }

    Course(const Course& other) : courseID(other.courseID), numOfLectures(other.numOfLectures), size(other.size) {
        lectures = new Lecture*[other.size];
        for (int i = 0; i < size; i++) {
            lectures[i] = other.lectures[i];
        }
    }

    Course& operator=(const Course& other) {
        courseID = other.courseID;
        numOfLectures = other.numOfLectures;
        size = other.size;
        
        auto newLectures = new Lecture*[other.size];
        for (int i = 0; i < other.size; i++) {
            newLectures[i] = other.lectures[i];
        }

        delete [] lectures;
        lectures = newLectures;
        return *this;
    }

    int addLecture() {
        lectures[numOfLectures] = nullptr;
        numOfLectures++;

        if (numOfLectures == size) {
            expand();
        }
        return numOfLectures - 1;
    }

    bool lectureExists(int index) const {
        return index >= 0 && index < numOfLectures;
    }

    Lecture** findLecture(int index) const {
        if (!lectureExists(index)) {
            return nullptr;
        }
        return &lectures[index];
    }
};

#endif //BOOM2_0_COURSE_H
