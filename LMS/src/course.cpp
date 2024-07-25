#include "course.hpp"

Course::Course(CourseInfo &info) : post_id(0)
{
    interface = Interface::get_instance();
    name = info.name;
    credit = info.credit;
    class_num = info.class_num;
    prerequisite = info.prerequisite;
    time = info.time;
    majors_id = info.majors_id;
    prof = info.prof;
    id = info.id;
    capacity = info.capacity;
}

void Course::get_channel(User *user, unsigned int pid)
{
    if (!in_course(user))
        throw NO_PERMISSON_MESSAGE;
    if (pid != ALL_POSTS)
    {
        if (!channel.contains(pid))
            throw NOT_FOUND_MESSAGE;
        print();
        *interface << pid << ' ' << channel[pid].author << ' ' << channel[pid].title
                   << ' ' << channel[pid].message << endl;
        return;
    }
    print();
    for (auto it = channel.rbegin(); it != channel.rend(); ++it)
    {
        auto &[pid, post] = *it;
        *interface << pid << ' ' << post.author << ' ' << post.title << endl;
    }
}

bool Course::in_teach_team(User *user)
{
    if (find(teach_team.begin(), teach_team.end(), user) == teach_team.end())
        return false;
    return true;
}

bool Course::in_course(User *user)
{
    if (in_teach_team(user))
        return true;
    auto st = dynamic_cast<Student *>(user);
    if (!st)
        return false;
    if (find(students.begin(), students.end(), st) == students.end())
        return false;
    return true;
}

void Course::add_post(User *logged, Post &p)
{
    if (!in_teach_team(logged))
        throw NO_PERMISSON_MESSAGE;
    channel[id_gen()] = p;
    auto notif = Notification(id, name, NEW_CP_MESSAGE);
    for_each(students.begin(), students.end(), [&notif](Student *st)
             { st->notify(notif); });
    for_each(teach_team.begin(), teach_team.end(), [&logged, &notif](User *user)
             { 
        if(logged != user)
            user->notify(notif); });
}

void Course::add_teach_team(User *user)
{
    teach_team.push_back(user);
}

void Course::add_student(Student *st)
{
    students.push_back(st);
}

bool Course::operator==(const Course &other) const
{
    return other.id == id;
}

bool Course::coincide(const Schedule &time, bool prof) const
{
    if (time.weekday == this->time.weekday && !(time.end <= this->time.start || time.start >= this->time.end))
        return true;
    else if (prof)
        return false;
    else
        return this->time.exam_date == time.exam_date;
}

bool Course::approve_prerequisite(unsigned int semester, bool ta)
{
    if (ta)
        return semester > this->prerequisite;
    return semester >= this->prerequisite;
}

void Course::print(bool verbose)
{
    *interface << id << ' ' << name << ' ' << capacity << ' ' << prof;
    if (verbose)
        *interface << ' ' << time.weekday << ':' << time.start << '-' << time.end << ' ' << time.exam_date << ' ' << class_num;
    *interface << endl;
}