#include "admin.hpp"

Admin::Admin(string n, string p) : User()
{
    id = ADMIN_ID;
    name = n;
    password = p;
}

void Admin::connect(User *user)
{
    connections.push_back(user);
}

void Admin::print_page(map<unsigned int, string> &majors)
{
    *interface << name << endl;
    for (auto it = posts.rbegin(); it != posts.rend(); ++it)
    {
        auto &[post_id, post] = *it;
        *interface << post_id << ' ' << post.title << endl;
    }
}

void Admin::print_post(unsigned int p_id, map<unsigned int, string> &majors)
{
    if (!posts.contains(p_id))
        throw NOT_FOUND_MESSAGE;

    *interface << name << endl;
    *interface << p_id << ' ' << posts[p_id].title << ' ' << posts[p_id].message << endl;
}