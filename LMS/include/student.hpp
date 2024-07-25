#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "defs.hpp"
#include "user.hpp"
#include "interface.hpp"
#include "course.hpp"

class Student : public User
{
public:
    ~Student() = default;
    Student(StudentInfo &info);
    void enroll_course(Course *course);
    void del_course(unsigned int cid);
    bool busy(const Schedule &time) const;
    void print_page(map<unsigned int, string> &majors);
    void print_post(unsigned int pid, map<unsigned int, string> &majors);
    void print_courses();
    unsigned int get_semester() { return semester; }

private:
    unsigned int semester;
};

#endif