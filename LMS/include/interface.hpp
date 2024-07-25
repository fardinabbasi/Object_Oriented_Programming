#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <tuple>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "defs.hpp"

const char CSV_DELIM = ',';
const char MAJOR_DELIM = ';';

class Interface
{
public:
    ~Interface() = default;
    Interface(const Interface &obj) = delete;
    static Interface *get_instance();
    static void del_instance();
    tuple<map<unsigned int, string>, map<unsigned int, StudentInfo>,
          map<unsigned int, CourseInfo>, map<unsigned int, ProfInfo>>
    read_files(const map<string, string> files_path);
    bool get_line(string &line, const char delim = '\n');
    template <typename T>
    Interface &operator<<(const T &value)
    {
        cout << value;
        return *this;
    }
    Interface &operator<<(ostream &(*manipulator)(ostream &));
    static CSV_info read_csv(const string path);

private:
    Interface(){};
    static Interface *instance;
    map<unsigned int, string> read_majors(const string path);
    map<unsigned int, CourseInfo> read_courses(const string path);
    map<unsigned int, StudentInfo> read_students(const string path);
    map<unsigned int, ProfInfo> read_profs(const string path);
};

#endif