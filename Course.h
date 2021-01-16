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
        auto newData = new int[size*GROWTH_FACTOR];
        for (int i = 0; i < size*GROWTH_FACTOR; i++) {
            newData[i] = (i < size) ? lectures[i] : 0;
        }
        size = size*GROWTH_FACTOR;

        delete [] lectures;
        lectures = newData;
    }

    bool indexInBounds(int index) const {
        return index >= 0 && index < numOfLectures;
    }

public:
    int courseID;
    int numOfLectures = 0;
    int* lectures = nullptr; /** DynamicArray of pointers to lecture vertices */

    explicit Course(int courseID = 0) : courseID(courseID), lectures(new int[INITIAL_CAPACITY]) {
        for (int i = 0; i < INITIAL_CAPACITY; i++) {
            lectures[i] = 0;
        }
    };

    ~Course() {
        delete [] lectures; //TODO: check if entered when hashTable gets deleted
    }

    Course(const Course& other) : size(other.size), courseID(other.courseID), numOfLectures(other.numOfLectures) {
        lectures = new int[other.size];
        for (int i = 0; i < size; i++) {
            lectures[i] = other.lectures[i];
        }
    }

    Course& operator=(const Course& other) {
        auto newLectures = new int[other.size];
        for (int i = 0; i < other.size; i++) {
            newLectures[i] = other.lectures[i];
        }
        delete [] lectures;
        lectures = newLectures;

        courseID = other.courseID;
        numOfLectures = other.numOfLectures;
        size = other.size;
        return *this;
    }

    int addLecture() {
        numOfLectures++;

        if (numOfLectures == size) {
            expand();
        }
        return numOfLectures - 1;
    }

    int findLectureTime(int index) const {
        if (!indexInBounds(index)) {
            return 0;
        }
        return lectures[index];
    }

    void addLectureTime(int index, int lectureTime) {
        if (!indexInBounds(index)) {
            return;
        }
        lectures[index] = lectureTime;
    }
};

#endif //BOOM2_0_COURSE_H
