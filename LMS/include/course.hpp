#ifndef COURSE_HPP
#define COURSE_HPP

#include <algorithm>
#include "defs.hpp"
#include "interface.hpp"
#include "user.hpp"
#include "student.hpp"

class Course
{
public:
    ~Course() = default;
    Course(){};
    Course(CourseInfo &info);
    bool operator==(const Course &other) const;
    bool coincide(const Schedule &time, bool prof = false) const;
    bool approve_prerequisite(unsigned int semester, bool ta = false);
    set<unsigned int> get_majors() { return majors_id; }
    Schedule get_time() { return time; }
    string get_name() { return name; }
    unsigned int get_id() { return id; }
    void print(bool verbose = true);
    void add_post(User *logged, Post &p);
    void get_channel(User *user, unsigned int pid = ALL_POSTS);
    void add_teach_team(User *user);
    void add_student(Student *st);

private:
    Interface *interface;
    string name, prof;
    unsigned int id, post_id, credit, prerequisite, class_num, capacity;
    Schedule time;
    set<unsigned int> majors_id;
    map<unsigned int, Post> channel;
    list<Student *> students;
    list<User *> teach_team;
    unsigned int id_gen()
    {
        post_id += 1;
        return post_id;
    }
    bool in_course(User *user);
    bool in_teach_team(User *user);
};

#endif