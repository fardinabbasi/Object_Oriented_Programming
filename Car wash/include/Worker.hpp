#ifndef WORKER_HPP
#define WORKER_HPP

#include <optional>
#include <string>

using namespace std;

class Worker{
    public:
    Worker(){}
    Worker(const unsigned int id, const unsigned int stage_id, const unsigned int finish_time): 
    id(id), stage_id(stage_id), finish_time(finish_time) {}
    unsigned int get_id() const{ return id; }
    unsigned int get_stage() const{ return stage_id; }
    unsigned int get_finish_time() const{ return finish_time; }
    string get_status(bool print_mode=false);
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