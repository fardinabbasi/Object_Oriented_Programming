#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "defs.hpp"
#include "user.hpp"

class Admin : public User
{
public:
    ~Admin() = default;
    Admin(string n = ADMIN_NAME, string p = ADMIN_PASS);
    void connect(User *user);
    void print_page(map<unsigned int, string> &majors);
    void print_post(unsigned int post_id, map<unsigned int, string> &majors);
};

#endif