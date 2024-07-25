#ifndef UTMS_HPP
#define UTMS_HPP

#include <algorithm>
#include <regex>
#include <tuple>
#include "defs.hpp"
#include "user.hpp"
#include "student.hpp"
#include "prof.hpp"
#include "admin.hpp"
#include "course.hpp"
#include "interface.hpp"

class UTMS
{
public:
    UTMS(const map<string, string> files_path);
    void read_commands();
    ~UTMS();

private:
    static tuple<string, string, string> command_splitter(const string line);
    void login(const string args);
    void logout(const string args);
    void get_courses(const string args);
    void validate_post(const string args);
    void validate_del_post(const string args);
    void get_page(const string args);
    void get_post(const string args);
    void validate_connect(const string args);
    void get_notification(const string args);
    void validate_course_offer(const string args);
    void course_offer(CourseInfo info, unsigned int prof_id,
                      unsigned int capacity, Schedule time, unsigned int class_num);
    void validate_enroll_course(const string args);
    void validate_del_course(const string args);
    void get_my_courses(const string args);
    static Schedule extract_time(const string time, const string exam_date);
    unsigned int id_gen();
    void validate_add_prof_photo(const string args);
    void validate_course_post(const string args);
    void validate_course_channel(const string args);
    void validate_ta_form(const string args);
    void validate_close_form(const string args);
    void validate_ta_req(const string args);
    void get_course_post(const string args);
    User *logged;
    map<unsigned int, CourseInfo> courses;
    map<unsigned int, User *> users;
    map<unsigned int, Course *> offered_courses;
    map<unsigned int, string> majors;
    unsigned int course_id;
    Interface *interface;
    map<string, map<string, void (UTMS::*)(const string)>> commands;
};

#endif