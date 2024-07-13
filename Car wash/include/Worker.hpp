#ifndef WORKER_HPP
#define WORKER_HPP

#include "defs.hpp"
#include <iostream>
#include <optional>
#include <string>

class Worker
{
public:
    Worker() {}
    Worker(map<string, unsigned int> info) : id(info["Id"]), stage_id(info["Stage_Id"]), finish_time(info["Time_to_finish"]) {}
    unsigned int get_id() const { return id; }
    unsigned int get_stage() const { return stage_id; }
    unsigned int get_finish_time() const { return finish_time; }
    string get_status(bool print_mode = false);
    void do_job(unsigned int car);
    void pass_time(unsigned int t);

private:
    unsigned int id;
    unsigned int stage_id;
    unsigned int finish_time;
    optional<unsigned int> till_deadline;
    unsigned int car;
};

#endif