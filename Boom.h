//
// Created by tolev on 1/10/2021.
//

#ifndef BOOM2_0_BOOM_H
#define BOOM2_0_BOOM_H


#include "HashTable.h"
#include "AVL.h"
#include "Lecture.h"
#include "library2.h"

class Boom {
private:
    HashTable courseTable;
    AVL<Lecture> lecturesTree;
public:
    Boom() = default;

    ~Boom() = default;

    /**
     * @param courseID is the key of the new course
     */
    StatusType AddCourse(int courseID);

    /**
     * @param courseID is the key of the course to remove
     */
    StatusType RemoveCourse(int courseID);

    /**
     * @param courseID is the key of the course
     * @param classID is a reference int to return classID of new lecture
     */
    StatusType AddClass(int courseID, int* classID);

    /**
     * @param courseID index of the course in which the lecture exists
     * @param classID index of lecture to watch
     * @param time to watch
     */
    StatusType WatchClass(int courseID, int classID, int time);

    /**
     * @param courseID index of the course in which the lecture exists
     * @param classID index of lecture to check watching time
     * @param timeViewed is a reference int to return time watched data
     */
    StatusType TimeViewed(int courseID, int classID, int *timeViewed);

    /**
     * @param i index of lecture by viewing time to return
     * @param courseID is a reference int to return the courseID
     * @param classID is a reference int to return the classID
     */
    StatusType GetIthWatchedClass(int i, int* courseID, int* classID);
};


#endif //BOOM2_0_BOOM_H
