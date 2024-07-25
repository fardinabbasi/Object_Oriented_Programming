#include "utms.hpp"

UTMS::UTMS(const map<string, string> files_path) : logged(nullptr), course_id(0)
{
    interface = Interface::get_instance();
    auto [majors, students, courses, profs] = interface->read_files(files_path);
    this->majors = majors;
    this->courses = courses;
    User *new_user;
    users[ADMIN_ID] = new Admin();
    for (auto &[id, info] : students)
    {
        new_user = new Student(info);
        users[id] = new_user;
        users[ADMIN_ID]->connect(new_user);
    }
    for (auto &[id, info] : profs)
    {
        new_user = new Prof(info);
        users[id] = new_user;
        users[ADMIN_ID]->connect(new_user);
    }

  commands.insert({
    {"GET", {
        {"courses", &UTMS::get_courses},
        {"personal_page", &UTMS::get_page},
        {"post", &UTMS::get_post},
        {"notification", &UTMS::get_notification},
        {"my_courses", &UTMS::get_my_courses},
        {"course_channel", &UTMS::validate_course_channel},
        {"course_post", &UTMS::get_course_post}
    }},
    {"POST", {
        {"login", &UTMS::login},
        {"logout", &UTMS::logout},
        {"post", &UTMS::validate_post},
        {"connect", &UTMS::validate_connect},
        {"course_offer", &UTMS::validate_course_offer},
        {"profile_photo", &UTMS::validate_add_prof_photo},
        {"course_post", &UTMS::validate_course_post},
        {"ta_form", &UTMS::validate_ta_form},
        {"close_ta_form", &UTMS::validate_close_form},
        {"ta_request", &UTMS::validate_ta_req}
    }},
    {"DELETE", {
        {"post", &UTMS::validate_del_post},
        {"my_courses", &UTMS::validate_del_course}
    }},
    {"PUT", {
        {"my_courses", &UTMS::validate_enroll_course}
    }}
    });
}

void UTMS::read_commands()
{
    string line;
    while (interface->get_line(line))
    {
        try
        {
            auto [method, command, args] = command_splitter(line);
            if (!commands.contains(method))
                throw BAD_REQUEST_MESSAGE;
            if (!commands[method].contains(command))
                throw NOT_FOUND_MESSAGE;
            if (!logged && command != "login")
                throw NO_PERMISSON_MESSAGE;
            (this->*commands[method][command])(args);
            if (method != "GET" && command != "close_ta_form")
                *interface << SUCCESSFUL_MESSAGE << endl;
        }
        catch (const string e)
        {
            *interface << e << endl;
        }
    }
}

tuple<string, string, string> UTMS::command_splitter(const string line)
{
    regex pattern(INIT_COMMAND_REGEX);
    smatch matches;
    string method, command, args;
    if (regex_match(line, matches, pattern))
    {
        method = matches.str(1);
        command = matches.str(2);
        args = matches.str(3);
    }
    else
        throw BAD_REQUEST_MESSAGE;
    return make_tuple(method, command, args);
}

void UTMS::get_course_post(const string args)
{
    regex pattern(GET_COURSE_POST_REGEX);
    smatch matches;
    unsigned int cid, post_id;
    if (regex_match(args, matches, pattern))
    {
        if (matches[2].matched && matches[3].matched)
        {
            cid = stoul(matches[2]);
            post_id = stoul(matches[3]);
        }
        else if (matches[4].matched && matches[5].matched)
        {
            post_id = stoul(matches[4]);
            cid = stoul(matches[5]);
        }
    }
    else
        throw BAD_REQUEST_MESSAGE;
    if (!offered_courses.contains(cid))
        throw NOT_FOUND_MESSAGE;
    offered_courses[cid]->get_channel(logged, post_id);
}

void UTMS::validate_ta_form(const string args)
{
    regex pattern(ADD_TA_FORM_REGEX);
    smatch matches;
    unsigned int id;
    string title, message;
    if (regex_match(args, matches, pattern))
    {
        if (matches[2].matched && matches[3].matched)
        {
            id = stoul(matches[2]);
            message = matches[3];
        }
        else if (matches[4].matched && matches[5].matched)
        {
            message = matches[4];
            id = stoul(matches[5]);
        }
    }
    else
        throw BAD_REQUEST_MESSAGE;
    if (!offered_courses.contains(id))
        throw NOT_FOUND_MESSAGE;
    title = NEW_FORM_TITLE + ' ' + offered_courses[id]->get_name() + " course";

    logged->ta_form(Post(title, message, id));
}

void UTMS::validate_ta_req(const string args)
{
    Student *st = dynamic_cast<Student *>(logged);
    if (!st)
        throw NO_PERMISSON_MESSAGE;
    regex pattern(APPLY_TA_REGEX);
    smatch matches;
    unsigned int pid, fid;
    if (regex_match(args, matches, pattern))
    {
        if (matches[2].matched && matches[3].matched)
        {
            pid = stoul(matches[2]);
            fid = stoul(matches[3]);
        }
        else if (matches[4].matched && matches[5].matched)
        {
            fid = stoul(matches[4]);
            pid = stoul(matches[5]);
        }
    }
    else
        throw BAD_REQUEST_MESSAGE;
    if (!dynamic_cast<Prof *>(users[pid]))
        throw NOT_FOUND_MESSAGE;
    users[pid]->add_ta_req(fid, st);
}

void UTMS::validate_close_form(const string args)
{
    regex pattern(ID_REGEX);
    smatch matches;
    unsigned int fid;
    if (regex_match(args, matches, pattern))
        fid = stoul(matches[1]);
    else
        throw BAD_REQUEST_MESSAGE;
    logged->close_form(fid);
}

void UTMS::validate_course_channel(const string args)
{
    regex pattern(ID_REGEX);
    smatch matches;
    unsigned int cid;
    if (regex_match(args, matches, pattern))
        cid = stoul(matches[1]);
    else
        throw BAD_REQUEST_MESSAGE;
    if (!offered_courses.contains(cid))
        throw NOT_FOUND_MESSAGE;
    offered_courses[cid]->get_channel(logged);
}

void UTMS::validate_course_post(const string args)
{
    map<string, string> split;
    map<string, regex> patterns = {
        {"title", regex(R"(\btitle\b\s+(".*?"))")},
        {"message", regex(R"(\bmessage\b\s+(".*?"))")},
        {"image", regex(R"(\bimage\b\s+(\S+))")},
        {"id", regex(R"(\bid\b\s+(\d+))")}};
    smatch matches;
    for (auto &pattern : patterns)
    {
        if (regex_search(args, matches, pattern.second))
        {
            split[pattern.first] = matches.str(1);
        }
        else if (pattern.first != "image")
            throw BAD_REQUEST_MESSAGE;
    }
    unsigned int cid = stoul(split["id"]);
    if (!offered_courses.contains(cid))
        throw NOT_FOUND_MESSAGE;
    auto p = Post(split["title"], split["message"], split["image_path"], logged->get_name());
    offered_courses[cid]->add_post(logged, p);
}

void UTMS::get_courses(const string args)
{
    if (args.empty())
    {
        if (offered_courses.empty())
            throw EMPTY_MESSAGE;
        for_each(offered_courses.begin(), offered_courses.end(),
                 [this](const pair<const unsigned int, Course *> &course)
                 { course.second->print(false); });
    }
    else
    {
        regex pattern(ID_REGEX);
        smatch matches;
        unsigned int id;
        if (regex_match(args, matches, pattern))
            id = stoul(matches[1]);
        else
            throw BAD_REQUEST_MESSAGE;
        if (!offered_courses.contains(id))
            throw NOT_FOUND_MESSAGE;
        offered_courses[id]->print();
    }
}

void UTMS::get_page(const string args)
{
    regex pattern(ID_REGEX);
    smatch matches;
    unsigned int id;
    if (regex_match(args, matches, pattern))
        id = stoul(matches[1]);
    else
        throw BAD_REQUEST_MESSAGE;
    if (!users.contains(id))
        throw NOT_FOUND_MESSAGE;
    users[id]->print_page(majors);
}

void UTMS::get_post(const string args)
{
    regex pattern(GET_POST);
    smatch matches;
    unsigned int id, post_id;
    if (regex_match(args, matches, pattern))
    {
        if (matches[2].matched && matches[3].matched)
        {
            id = stoul(matches[2]);
            post_id = stoul(matches[3]);
        }
        else if (matches[4].matched && matches[5].matched)
        {
            post_id = stoul(matches[4]);
            id = stoul(matches[5]);
        }
    }
    else
        throw BAD_REQUEST_MESSAGE;
    if (!users.contains(id))
        throw NOT_FOUND_MESSAGE;
    users[id]->print_post(post_id, majors);
}

void UTMS::get_notification(const string args)
{
    if (!args.empty())
        throw BAD_REQUEST_MESSAGE;
    logged->print_notifs();
}

void UTMS::get_my_courses(const string args)
{
    if (!args.empty())
        throw BAD_REQUEST_MESSAGE;

    logged->print_courses();
}

void UTMS::login(const string args)
{
    if (logged)
        throw NO_PERMISSON_MESSAGE;
    regex pattern(LOGIN_REGEX);
    smatch matches;
    unsigned int id;
    string password;
    if (regex_match(args, matches, pattern))
    {
        if (matches[2].matched && matches[3].matched)
        {
            id = stoul(matches[2]);
            password = matches[3];
        }
        else if (matches[4].matched && matches[5].matched)
        {
            password = matches[4];
            id = stoul(matches[5]);
        }
    }
    else
        throw BAD_REQUEST_MESSAGE;
    if (!users.contains(id))
        throw NOT_FOUND_MESSAGE;
    if (!users[id]->authenticate(password))
        throw NO_PERMISSON_MESSAGE;
    logged = users[id];
}

void UTMS::validate_course_offer(const string args)
{
    if (!dynamic_cast<Admin *>(logged))
        throw NO_PERMISSON_MESSAGE;
    unsigned int course_id, prof_id, capacity, class_num;
    map<string, string> split;
    map<string, regex> patterns = {
        {"cid", regex(R"(\bcourse_id\b\s+(\d+))")},
        {"pid", regex(R"(\bprofessor_id\b\s+(\d+))")},
        {"capacity", regex(R"(\bcapacity\b\s+(\d+))")},
        {"time", regex(R"(\btime\b\s+(\S+))")},
        {"exam", regex(R"(\bexam_date\b\s+(\S+))")},
        {"class_num", regex(R"(\bclass_number\b\s+(\d+))")}};
    smatch matches;
    for (auto &pattern : patterns)
    {
        if (regex_search(args, matches, pattern.second))
        {
            split[pattern.first] = matches.str(1);
        }
        else
            throw BAD_REQUEST_MESSAGE;
    }
    course_id = stoul(split["cid"]);
    prof_id = stoul(split["pid"]);
    capacity = stoul(split["capacity"]);
    class_num = stoul(split["class_num"]);

    if (!courses.contains(course_id) || !users.contains(prof_id))
        throw NOT_FOUND_MESSAGE;
    if (!dynamic_cast<Prof *>(users[prof_id]))
        throw NO_PERMISSON_MESSAGE;
    course_offer(courses[course_id], prof_id, capacity,
                 extract_time(split["time"], split["exam"]), class_num);
}

void UTMS::course_offer(CourseInfo info, unsigned int prof_id, unsigned int capacity,
                        Schedule time, unsigned int class_num)
{
    User *prof = users[prof_id];
    string prof_name = prof->get_name();
    unsigned int new_id = course_id + 1;
    info.add(new_id, prof_name, capacity, class_num, time);

    Course *new_course = new Course(info);
    try
    {
        prof->enroll_course(new_course);
    }
    catch (const string e)
    {
        delete new_course;
        throw;
    }
    new_id = id_gen();
    offered_courses[new_id] = new_course;
    new_course->add_teach_team(prof);
    Notification notif = Notification(prof_id, prof_name, COURSE_OFFERING_MESSAGE);
    for_each(users.begin(), users.end(), [&notif](pair<const unsigned int, User *> &user)
             { user.second->notify(notif); });
}

unsigned int UTMS::id_gen()
{
    course_id += 1;
    return course_id;
}

void UTMS::logout(const string args)
{
    if (!args.empty())
        throw BAD_REQUEST_MESSAGE;
    logged = nullptr;
}

UTMS::~UTMS()
{
    for_each(users.begin(), users.end(), [](pair<unsigned int, User *> user)
             { delete user.second; });
    for_each(offered_courses.begin(), offered_courses.end(), [](pair<unsigned int, Course *> course)
             { delete course.second; });
}

void UTMS::validate_post(const string args)
{
    map<string, string> split;
    map<string, regex> patterns = {
        {"title", regex(R"(\btitle\b\s+(".*?"))")},
        {"message", regex(R"(\bmessage\b\s+(".*?"))")},
        {"image", regex(R"(\bimage\b\s+(\S+))")}};
    smatch matches;
    for (auto &pattern : patterns)
    {
        if (regex_search(args, matches, pattern.second))
        {
            split[pattern.first] = matches.str(1);
        }
        else if (pattern.first != "image")
            throw BAD_REQUEST_MESSAGE;
    }

    logged->add_post(Post(split["title"], split["message"], split["image"]));
}

void UTMS::validate_enroll_course(const string args)
{
    regex pattern(ID_REGEX);
    smatch matches;
    unsigned int id;
    if (regex_match(args, matches, pattern))
        id = stoul(matches[1]);
    else
        throw BAD_REQUEST_MESSAGE;

    if (!offered_courses.contains(id))
        throw NOT_FOUND_MESSAGE;

    logged->enroll_course(offered_courses[id]);
}

void UTMS::validate_add_prof_photo(const string args)
{
    regex pattern(ADD_PHOTO_REGEX);
    smatch matches;
    string photo_path;
    if (regex_match(args, matches, pattern))
        photo_path = matches[1];
    else
        throw BAD_REQUEST_MESSAGE;
}

void UTMS::validate_del_course(const string args)
{
    regex pattern(ID_REGEX);
    smatch matches;
    unsigned int id;
    if (regex_match(args, matches, pattern))
        id = stoul(matches[1]);
    else
        throw BAD_REQUEST_MESSAGE;

    if (!offered_courses.contains(id))
        throw BAD_REQUEST_MESSAGE;

    logged->del_course(id);
}

void UTMS::validate_del_post(const string args)
{
    regex pattern(ID_REGEX);
    smatch matches;
    unsigned int id;
    if (regex_match(args, matches, pattern))
        id = stoul(matches[1]);
    else
        throw BAD_REQUEST_MESSAGE;

    logged->del_post(id);
}

void UTMS::validate_connect(const string args)
{
    regex pattern(ID_REGEX);
    smatch matches;
    unsigned int id;
    if (regex_match(args, matches, pattern))
        id = stoul(matches[1]);
    else
        throw BAD_REQUEST_MESSAGE;
    if (dynamic_cast<Admin *>(logged) || id == ADMIN_ID)
        throw NO_PERMISSON_MESSAGE;
    if (!users.contains(id))
        throw NOT_FOUND_MESSAGE;

    logged->connect(users[id]);
}

Schedule UTMS::extract_time(const string time, const string exam_date)
{
    string weekday;
    unsigned int start, end;
    regex pattern(TIME_REGEX);
    smatch matches;
    if (regex_match(time, matches, pattern))
    {
        weekday = matches[1].str();
        start = stoul(matches[2].str());
        end = stoul(matches[3].str());
    }
    return Schedule(weekday, start, end, exam_date);
}