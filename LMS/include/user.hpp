#ifndef USER_HPP
#define USER_HPP

#include <algorithm>
#include "defs.hpp"
#include "interface.hpp"

class Course;
class Student;

class User
{
public:
    ~User() = default;
    User();
    void print_notifs();
    void del_post(unsigned int id);
    bool authenticate(const string p) { return p == password; }
    virtual bool busy(const Schedule &time) const { return false; };
    bool approve_major(set<unsigned int> majors);
    virtual string get_name() { return name; }
    virtual unsigned int get_id() { return id; }
    void notify(Notification notif);
    virtual void connect(User *user);
    void add_post(Post p, const string notif_message = NEW_POST_MESSAGE);
    virtual void ta_form(Post p) { throw NO_PERMISSON_MESSAGE; }
    virtual void enroll_course(Course *course) { throw NO_PERMISSON_MESSAGE; };
    virtual void del_course(unsigned int cid) { throw NO_PERMISSON_MESSAGE; };
    virtual void print_page(map<unsigned int, string> &majors) = 0;
    virtual void print_post(unsigned int pid, map<unsigned int, string> &majors) = 0;
    virtual void print_courses() { throw NO_PERMISSON_MESSAGE; };
    virtual void add_ta_req(unsigned int fid, Student *st) { throw NO_PERMISSON_MESSAGE; };
    virtual void close_form(unsigned int fid) { throw NO_PERMISSON_MESSAGE; };

protected:
    map<unsigned int, Post> posts;
    list<User *> connections;
    map<unsigned int, Course *> courses;
    unsigned int id, post_id, major_id;
    string name;
    string password;
    Interface *interface;

private:
    unsigned int id_gen();
    list<Notification> notifs;
};

#endif