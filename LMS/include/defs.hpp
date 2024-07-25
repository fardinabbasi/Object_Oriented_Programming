#ifndef DEFS_HPP
#define DEFS_HPP

#include <string>
#include <list>
#include <set>
#include <map>
#include <iostream>

using namespace std;
typedef list<map<string, string>> CSV_info;

const unsigned int MAJORS_FILE_INDEX = 1;
const unsigned int STUDENTS_FILE_INDEX = 2;
const unsigned int COURSES_FILE_INDEX = 3;
const unsigned int PROFS_FILE_INDEX = 4;
const unsigned int ARGS_NUM = 5;
const string FILE_FAILED_MESSAGE = "Failed to open the file!";
const string ARGS_FAILED_MESSAGE = "Inadequate arguments!";
const string EMPTY_MESSAGE = "Empty";
const string SUCCESSFUL_MESSAGE = "OK";
const string NOT_FOUND_MESSAGE = "Not Found";
const string BAD_REQUEST_MESSAGE = "Bad Request";
const string NO_PERMISSON_MESSAGE = "Permission Denied";
const unsigned int ADMIN_ID = 0;
const string ADMIN_PASS = "UT_account";
const string ADMIN_NAME = "UT_account";
const char COMMAND_STARTER = '?';
const string COURSE_OFFERING_MESSAGE = "New Course Offering";
const string NEW_POST_MESSAGE = "New Post";
const string NEW_FORM_MESSAGE = "New Form";
const string NEW_CP_MESSAGE = "New Course Post";
const string NEW_FORM_TITLE = "TA form for";
const string GET_COURSE_MESSAGE = "Get Course";
const string DEL_COURSE_MESSAGE = "Delete Course";
const string ACC_TA_INP = "accept";
const string REJ_TA_INP = "reject";
const string TA_ANS_MESSAGE = "Your request to be a teaching assistant has been ";
const pair<string, string> NUM_TA_MESSAGE = make_pair("We have received ",
                                                      " requests for the teaching assistant position");

const string INIT_COMMAND_REGEX = R"((GET|PUT|DELETE|POST)\s+(\w+)\s+\?\s*(.*)\s*)";
const string GET_COURSE_POST_REGEX = R"((id\s+(\d+)\s+post_id\s+(\d+)\s*|post_id\s+(\d+)\s+id\s+(\d+)\s*))";
const string ADD_TA_FORM_REGEX = R"((course_id\s+(\d+)\s+message\s+(".*")\s*|message\s+(".*")\s+id\s+(\d+)\s*))";
const string APPLY_TA_REGEX = R"((professor_id\s+(\d+)\s+form_id\s+(\d+)\s*|form_id\s+(\d+)\s+professor_id\s+(\d+)\s*))";
const string GET_POST = R"((id\s+(\d+)\s+post_id\s+(\d+)\s*|post_id\s+(\d+)\s+id\s+(\d+)\s*))";
const string LOGIN_REGEX = R"((id\s+(\d+)\s+password\s+(.*?)\s*|password\s+(.*?)\s+id\s+(\d+)\s*))";
const string ID_REGEX = R"(id\s+(\d+))";
const string TIME_REGEX = R"((\w+):(\d+)-(\d+)\s*)";
const string ADD_PHOTO_REGEX = R"(photo\s+(\S+)$)";

const unsigned int ALL_POSTS = -1;
const unsigned int NOT_FORM = 0;

struct UserInfo
{
    UserInfo(){};
    string name, pass;
    unsigned int major_id, id;
};

struct StudentInfo : public UserInfo
{
    StudentInfo(){};
    StudentInfo(map<string, string> info) : UserInfo()
    {
        name = info["name"];
        pass = info["password"];
        major_id = stoul(info["major_id"]);
        semester = stoul(info["semester"]);
        id = stoul(info["sid"]);
    }
    unsigned int semester;
};

struct ProfInfo : public UserInfo
{
    ProfInfo(){};
    ProfInfo(map<string, string> info) : UserInfo()
    {
        name = info["name"];
        pass = info["password"];
        pos = info["position"];
        major_id = stoul(info["major_id"]);
        id = stoul(info["pid"]);
    }
    string pos;
};

struct Schedule
{
    Schedule(){};
    Schedule(string weekday, unsigned int start, unsigned int end, string exam_date) : weekday(weekday), start(start), end(end), exam_date(exam_date) {}
    string weekday, exam_date;
    unsigned int start, end;
};

struct CourseInfo
{
    CourseInfo(){};

    CourseInfo(map<string, string> info, set<unsigned int> majors_id) : majors_id(majors_id)
    {
        id = stoul(info["cid"]);
        credit = stoul(info["credit"]);
        prerequisite = stoul(info["prerequisite"]);
        name = info["name"];
    }

    void add(unsigned int id, string prof, unsigned int capacity, unsigned int class_num, Schedule time)
    {
        this->id = id;
        this->prof = prof;
        this->capacity = capacity;
        this->class_num = class_num;
        this->time = time;
    }

    unsigned int id, credit, prerequisite, class_num, capacity;
    Schedule time;
    string name, prof, exam_date;
    set<unsigned int> majors_id;
};

struct Notification
{
    Notification(){};
    Notification(unsigned int id, string name, string message = "") : id(id), name(name), message(message){};
    string name, message;
    unsigned int id;
};

struct Post
{
    Post(){};
    Post(string title, string message, string image_path = "", string author = "") : title(title),
                                                                                     message(message), image_path(image_path), cid(NOT_FORM), author(author){};
    Post(string title, string message, unsigned int cid) : title(title),
                                                           message(message), cid(cid) {}
    string title, message, image_path, author;
    unsigned int cid;
};

#endif