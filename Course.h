//
// Created by tolev on 06/01/2021.
//

#ifndef BOOM2_0_COURSE_H
#define BOOM2_0_COURSE_H

#define GROWTH_FACTOR 2
#define INITIAL_CAPACITY 4

#include "Lecture.h"

class Course {
    int size = 0;

    void expand() {
        auto newData = new Lecture*[size*GROWTH_FACTOR];
        for (int i = 0; i < size; i++) {
            newData[i] = lectures[i];
        }
        size = size*GROWTH_FACTOR;

        delete [] lectures;
        lectures = newData;
    }

public:
    int courseID;
    Lecture** lectures = nullptr; /** DynamicArray of pointers to lecture vertices */
    int numOfLectures = 0;

    explicit Course(int courseID)
            : courseID(courseID), lectures(new Lecture*[INITIAL_CAPACITY]) {};

    ~Course() {
        delete [] lectures; //TODO: check if entered when hashTable gets deleted
    }

    Course& operator=(const Course& other) = default; /** Only copies pointer to vertices array */

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

    Lecture* findLecture(int index) const {
        if (!lectureExists(index)) {
            return nullptr;
        }
        return lectures[index];
    }
};

#endif //BOOM2_0_COURSE_H
