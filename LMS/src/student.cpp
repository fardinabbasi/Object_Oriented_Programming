#include "student.hpp"

Student::Student(StudentInfo &info) : User()
{
    name = info.name;
    password = info.pass;
    major_id = info.major_id;
    semester = info.semester;
    id = info.id;
}

void Student::enroll_course(Course *course)
{
    if (!course->approve_prerequisite(semester) || !approve_major(course->get_majors()) || busy(course->get_time()))
        throw NO_PERMISSON_MESSAGE;
    courses[course->get_id()] = course;
    course->add_student(this);
    Notification notif = Notification(id, name, GET_COURSE_MESSAGE);
    for_each(connections.begin(), connections.end(), [&notif](User *user)
             { user->notify(notif); });
}

void Student::del_course(unsigned int cid)
{
    if (!courses.contains(cid))
        throw NOT_FOUND_MESSAGE;
    Notification notif = Notification(id, name, DEL_COURSE_MESSAGE);
    for_each(connections.begin(), connections.end(), [&notif](User *user)
             { user->notify(notif); });
    courses.erase(cid);
}

bool Student::busy(const Schedule &time) const
{
    return any_of(courses.begin(), courses.end(), [&time](pair<unsigned int, Course *> course)
                  { return course.second->coincide(time); });
}

void Student::print_page(map<unsigned int, string> &majors)
{
    bool first_iter = true;
    *interface << name << ' ' << majors[major_id] << ' ' << semester;
    for (auto &[_, course] : courses)
    {
        *interface << (first_iter ? ' ' : ',');
        *interface << course->get_name();
        first_iter = false;
    }
    *interface << endl;
    for (auto it = posts.rbegin(); it != posts.rend(); ++it)
    {
        auto &[post_id, post] = *it;
        *interface << post_id << ' ' << post.title << endl;
    }
}

void Student::print_post(unsigned int pid, map<unsigned int, string> &majors)
{
    if (!posts.contains(pid))
        throw NOT_FOUND_MESSAGE;
    bool first_iter = true;
    *interface << name << ' ' << majors[major_id] << ' ' << semester;
    for (auto &[_, course] : courses)
    {
        *interface << (first_iter ? ' ' : ',');
        *interface << course->get_name();
        first_iter = false;
    }
    *interface << endl;

    *interface << pid << ' ' << posts[pid].title << ' ' << posts[pid].message << endl;
}

void Student::print_courses()
{
    if (courses.empty())
        throw EMPTY_MESSAGE;
    for_each(courses.begin(), courses.end(), [](pair<unsigned int, Course *> course)
             { course.second->print(); });
}