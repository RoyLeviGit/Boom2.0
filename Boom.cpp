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
            int lectureTime = course->findLectureTime(i);
            if (lectureTime != 0) {
                lecturesTree.remove(Lecture(courseID, i, lectureTime));
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
        int lectureTime = course->findLectureTime(classID);
        if(lectureTime != 0) {
            lecturesTree.remove(Lecture(courseID, classID, lectureTime));
        }
        course->addLectureTime(classID, lectureTime + time);
        lecturesTree.insert(Lecture(courseID, classID, lectureTime + time));
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

    *timeViewed = course->findLectureTime(classID);
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
