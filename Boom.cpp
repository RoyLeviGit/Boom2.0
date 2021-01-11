//
// Created by tolev on 1/10/2021.
//

#include "Boom.h"

StatusType Boom::AddCourse(int courseID) {
    if (courseID <= 0) {
        return INVALID_INPUT;
    }
    if (courseTable.find(courseID) != nullptr) {
        return FAILURE;
    }

    try {
        courseTable.insert(Course(courseID));
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Boom::RemoveCourse(int courseID) {
    if (courseID <= 0) {
        return INVALID_INPUT;
    }
    Course* course = courseTable.find(courseID);
    if (course == nullptr) {
        return FAILURE;
    }

    try {
        for (int i = 0; i < course->numOfLectures; i++) {
            Lecture** lecture = course->findLecture(i);
            if (*lecture != nullptr) {
                lecturesTree.remove(**lecture);
            }
        }
        courseTable.remove(*course);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Boom::AddClass(int courseID, int *classID) {
    if (courseID <= 0) {
        return INVALID_INPUT;
    }
    Course* course = courseTable.find(courseID);
    if (course == nullptr) {
        return FAILURE;
    }

    try {
        *classID = course->addLecture();
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Boom::WatchClass(int courseID, int classID, int time) {
    if (courseID <= 0 || classID < 0 || time <= 0) {
        return INVALID_INPUT;
    }
    Course* course = courseTable.find(courseID);
    if (course == nullptr) {
        return FAILURE;
    }
    if (classID+1 > course->numOfLectures) {
        return INVALID_INPUT;
    }

    try {
        Lecture** lecture = course->findLecture(classID);
        int currentTime = 0;
        if(*lecture != nullptr) {
            currentTime = (*lecture)->time;
            lecturesTree.remove(Lecture(courseID, classID, currentTime));
        }
        *lecture = new Lecture(courseID, classID, currentTime + time);
        lecturesTree.insert(**lecture);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Boom::TimeViewed(int courseID, int classID, int *timeViewed) {
    if (courseID <= 0 || classID < 0) {
        return INVALID_INPUT;
    }
    Course* course = courseTable.find(courseID);
    if (course == nullptr) {
        return FAILURE;
    }
    if (classID+1 > course->numOfLectures) {
        return INVALID_INPUT;
    }

    Lecture** lecture = course->findLecture(classID);
    *timeViewed = (*lecture == nullptr) ? 0 : (*lecture)->time;
    return SUCCESS;
}

StatusType Boom::GetIthWatchedClass(int i, int* courseID, int* classID) {
    if (i <= 0) {
        return INVALID_INPUT;
    }
    const Lecture* lecture = lecturesTree.getRank(i);
    if(lecture == nullptr) {
        return FAILURE;
    }

    *courseID = lecture->courseID;
    *classID = lecture->lectureID;
    return SUCCESS;
}
