#include "interface.hpp"

Interface *Interface::instance = nullptr;

string trim(const string str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (start == string::npos)
        return "";
    else
        return str.substr(start, end - start + 1);
}

Interface *Interface::get_instance()
{
    if (!instance)
        instance = new Interface();
    return instance;
}

void Interface::del_instance()
{
    if (instance)
        delete instance;
}

CSV_info Interface::read_csv(const string path)
{
    ifstream fin(path);
    if (!fin.is_open())
    {
        cerr << FILE_FAILED_MESSAGE << endl;
    }
    CSV_info info;
    list<string> keys;
    string value, line, id;
    map<string, string> row;

    getline(fin, line);
    line = trim(line);
    stringstream ss(line);
    while (getline(ss, value, CSV_DELIM))
    {
        keys.push_back(value);
    }
    while (getline(fin, line))
    {
        row.clear();
        line = trim(line);
        stringstream ss(line);
        auto it = keys.begin();
        while (getline(ss, value, CSV_DELIM))
        {
            if (!value.empty())
            {
                row[*it] = value;
            }
            it++;
        }
        info.push_back(row);
    }
    fin.close();
    return info;
}

map<unsigned int, string> Interface::read_majors(const string path)
{
    CSV_info info = read_csv(path);
    map<unsigned int, string> majors;
    for_each(info.begin(), info.end(), [&majors](map<string, string> &row)
             { majors[stoul(row["mid"])] = row["major"]; });
    return majors;
}

map<unsigned int, StudentInfo> Interface::read_students(const string path)
{
    CSV_info info = read_csv(path);
    map<unsigned int, StudentInfo> students;
    for_each(info.begin(), info.end(), [&students](map<string, string> &row)
             { students[stoul(row["sid"])] = StudentInfo(row); });
    return students;
}

map<unsigned int, ProfInfo> Interface::read_profs(const string path)
{
    CSV_info info = read_csv(path);
    map<unsigned int, ProfInfo> profs;
    for_each(info.begin(), info.end(), [&profs](map<string, string> &row)
             { profs[stoul(row["pid"])] = ProfInfo(row); });
    return profs;
}

map<unsigned int, CourseInfo> Interface::read_courses(const string path)
{
    CSV_info info = read_csv(path);
    map<unsigned int, CourseInfo> courses;
    set<unsigned int> majors_id;
    string major_id;
    for_each(info.begin(), info.end(), [&](map<string, string> &row)
             {
        majors_id.clear();
        stringstream mm(row["majors_id"]);
        while (getline(mm, major_id, MAJOR_DELIM))
        {
            majors_id.insert(stoul(major_id));
        }
        row.erase("majors_id");
        courses[stoul(row["cid"])] = CourseInfo(row, majors_id); });
    return courses;
}

Interface &Interface::operator<<(ostream &(*manipulator)(ostream &))
{
    cout << manipulator;
    return *this;
}

tuple<map<unsigned int, string>, map<unsigned int, StudentInfo>,
      map<unsigned int, CourseInfo>, map<unsigned int, ProfInfo>>
Interface::read_files(const map<string, string> files_path)
{

    return make_tuple(read_majors(files_path.at("majors")), read_students(files_path.at("students")),
                      read_courses(files_path.at("courses")), read_profs(files_path.at("profs")));
}

bool Interface::get_line(string &line, const char delim)
{
    if (getline(cin, line, delim))
    {
        line = trim(line);
        return true;
    }
    return false;
}