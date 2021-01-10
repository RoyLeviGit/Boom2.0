//
// Created by tolev on 1/10/2021.
//

#include"library2.h"
#include"Boom.h"

void *Init() {
    Boom *DS = new Boom ();
    return (void*)DS;
}

StatusType AddCourse(void *DS, int courseID) {
    if(DS == nullptr) return INVALID_INPUT;
    return ((Boom *)DS)->AddCourse(courseID);
}

StatusType RemoveCourse(void *DS, int courseID) {
    if(DS == nullptr) return INVALID_INPUT;
    return ((Boom *)DS)->RemoveCourse(courseID);
}

StatusType AddClass(void* DS, int courseID, int* classID) {
    if(DS == nullptr) return INVALID_INPUT;
    return ((Boom *)DS)->AddClass(courseID, classID);
}

StatusType WatchClass(void *DS, int courseID, int classID, int time) {
    if(DS == nullptr) return INVALID_INPUT;
    return ((Boom *)DS)->WatchClass(courseID, classID, time);
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed) {
    if(DS == nullptr) return INVALID_INPUT;
    return ((Boom *)DS)->TimeViewed(courseID, classID, timeViewed);
}

StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID) {
    if(DS == nullptr) return INVALID_INPUT;
    return ((Boom *)DS)->GetIthWatchedClass(i, courseID, classID);
}

void Quit(void** DS) {
    delete *(Boom **)DS;
    *DS = nullptr;
}