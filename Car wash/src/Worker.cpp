#include <iostream>
#include "Worker.hpp"
#include "Defs.hpp"

using namespace std;

void Worker::pass_time(unsigned int t){
    if (till_deadline.has_value()){
        till_deadline.emplace(till_deadline.value()-t);
        if (till_deadline.value() == 0)
            till_deadline.reset();
    }
}

void Worker::do_job(unsigned int car) {
    till_deadline = finish_time;
    this-> car = car;
}

string Worker::get_status(bool print_mode){
    string status;
    if (!till_deadline.has_value()){
        status = WORKER_IDLE;
        if(print_mode)
            cout << status << endl;
    }
    else{
        status = to_string(car);
        if(print_mode)
            cout << "Working: " << status << endl;
    }
    return status;
}