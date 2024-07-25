#ifndef PROF_HPP
#define PROF_HPP

#include "defs.hpp"
#include "user.hpp"
#include "interface.hpp"
#include "student.hpp"
#include "course.hpp"

class Prof : public User
{
public:
    ~Prof() = default;
    Prof(ProfInfo &info);
    bool busy(const Schedule &time) const;
    void enroll_course(Course *course);
    void print_page(map<unsigned int, string> &majors);
    void print_post(unsigned int post_id, map<unsigned int, string> &majors);
    void ta_form(Post p);
    void add_ta_req(unsigned int fid, Student *st);
    void close_form(unsigned int fid);

private:
    string position;
    map<unsigned int, list<Student *>> applicants;
    void ans_ta_req(unsigned int fid);
};

#endif