#include "prof.hpp"

Prof::Prof(ProfInfo &info) : User()
{
    name = info.name;
    password = info.pass;
    major_id = info.major_id;
    position = info.pos;
    id = info.id;
}

bool Prof::busy(const Schedule &time) const
{
    return any_of(courses.begin(), courses.end(), [&time](pair<unsigned int, const Course *> course)
                  { return course.second->coincide(time, true); });
}

void Prof::enroll_course(Course *course)
{
    if (!approve_major(course->get_majors()) || busy(course->get_time()))
        throw NO_PERMISSON_MESSAGE;
    courses[course->get_id()] = course;
}

void Prof::print_page(map<unsigned int, string> &majors)
{
    bool first_iter = true;
    *interface << name << ' ' << majors[major_id] << ' ' << position;
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

void Prof::print_post(unsigned int pid, map<unsigned int, string> &majors)
{
    if (!posts.contains(pid))
        throw NOT_FOUND_MESSAGE;
    bool first_iter = true;
    *interface << name << ' ' << majors[major_id] << ' ' << position;
    for (auto &[_, course] : courses)
    {
        *interface << (first_iter ? ' ' : ',');
        *interface << course->get_name();
        first_iter = false;
    }
    *interface << endl;

    *interface << pid << ' ' << posts[pid].title;
    if (posts[pid].cid != NOT_FORM)
    {
        *interface << endl;
        courses[posts[pid].cid]->print();
    }
    else
        *interface << ' ';
    *interface << posts[pid].message << endl;
}

void Prof::ta_form(Post p)
{
    if (!courses.contains(p.cid))
        throw NO_PERMISSON_MESSAGE;
    add_post(p, NEW_FORM_MESSAGE);
}

void Prof::add_ta_req(unsigned int fid, Student *st)
{
    if (!posts.contains(fid))
        throw NOT_FOUND_MESSAGE;
    unsigned int cid = posts[fid].cid;
    if (cid == NOT_FORM)
        throw NOT_FOUND_MESSAGE;
    if (!courses[cid]->approve_prerequisite(st->get_semester(), true))
        throw NO_PERMISSON_MESSAGE;
    applicants[fid].push_back(st);
}

void Prof::close_form(unsigned int fid)
{
    if (!posts.contains(fid))
        throw NOT_FOUND_MESSAGE;
    if (posts[fid].cid == NOT_FORM)
        throw NOT_FOUND_MESSAGE;
    *interface << NUM_TA_MESSAGE.first << applicants[fid].size() << NUM_TA_MESSAGE.second << endl;
    ans_ta_req(fid);
    posts.erase(fid);
}

void Prof::ans_ta_req(unsigned int fid)
{
    auto cid = posts[fid].cid;
    string line;
    auto st = applicants[fid].begin();

    while (st != applicants[fid].end())
    {
        *interface << (*st)->get_id() << ' ' << (*st)->get_name() << ' '
                   << (*st)->get_semester() << ": ";
        interface->get_line(line);
        *interface << endl;
        if (line == ACC_TA_INP)
            courses[cid]->add_teach_team(*st);
        else if (line != REJ_TA_INP)
            continue;
        (*st)->notify(Notification(cid, courses[cid]->get_name(), TA_ANS_MESSAGE + line + "ed."));
        ++st;
    }
    applicants.erase(fid);
}