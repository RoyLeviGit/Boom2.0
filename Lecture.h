//
// Created by tolev on 06/01/2021.
//

#ifndef BOOM2_0_LECTURE_H
#define BOOM2_0_LECTURE_H

class Lecture {
public:
    int courseID;
    int lectureID;
    int time; /** only a reference and is not be deleted or initialised by Lecture */

    Lecture() = default; /** must exist for usage in AVL */
    Lecture(int courseID, int lectureID, int time) : courseID(courseID), lectureID(lectureID), time(time) {}

    Lecture(const Lecture& other) = default; /** must exist for usage in AVL */
    Lecture& operator=(const Lecture& other) = default; /** must exist for usage in AVL */
    ~Lecture() = default;

    // Boolean operators
    bool operator<(const Lecture& lecture) const {
        if (time == lecture.time) {
            if (courseID == lecture.courseID)
                return lectureID < lecture.lectureID;
            return courseID < lecture.courseID;
        }
        return time > lecture.time; /** bigger time means smaller in the AVL tree. */
    }
    bool operator==(const Lecture& lecture) const {
        return time == lecture.time
            && courseID == lecture.courseID
            && lectureID == lecture.lectureID;
    }
    bool operator!=(const Lecture& lecture) const {
        return !(*this == lecture);
    }
    bool operator>(const Lecture& lecture) const {
        return !(*this == lecture || *this < lecture);
    }
    bool operator<=(const Lecture& lecture) const {
        return !(*this > lecture);
    }
    bool operator>=(const Lecture& lecture) const {
        return !(*this < lecture);
    }
};

#endif //BOOM2_0_LECTURE_H
