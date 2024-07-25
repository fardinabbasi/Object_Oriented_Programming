#include "user.hpp"

User::User()
{
    interface = Interface::get_instance();
    post_id = 0;
}

bool User::approve_major(set<unsigned int> majors)
{
    if (majors.find(major_id) == majors.end())
        return false;
    else
        return true;
}

void User::notify(Notification notif)
{
    notifs.push_back(notif);
}

void User::connect(User *user)
{
    auto it = find(connections.begin(), connections.end(), user);
    if (it != connections.end())
        throw BAD_REQUEST_MESSAGE;
    connections.push_back(user);
    user->connections.push_back(this);
}

void User::add_post(Post p, const string notif_message)
{
    posts[id_gen()] = p;
    Notification notif = Notification(id, name, notif_message);
    for_each(connections.begin(), connections.end(), [&notif](User *user)
             { user->notify(notif); });
}

unsigned int User::id_gen()
{
    post_id += 1;
    return post_id;
}

void User::del_post(unsigned int id)
{
    if (!posts.contains(id))
        throw NOT_FOUND_MESSAGE;
    posts.erase(id);
}

void User::print_notifs()
{
    if (notifs.empty())
        throw EMPTY_MESSAGE;
    for (auto it = notifs.rbegin(); it != notifs.rend(); ++it)
    {
        *interface << it->id << ' ' << it->name << ": " << it->message << endl;
    }
    notifs.clear();
}