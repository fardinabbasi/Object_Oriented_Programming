#ifndef CARWASH_HPP
#define CARWASH_HPP

#include "defs.hpp"
#include "stage.hpp"
#include "worker.hpp"
#include "event.hpp"
#include "car.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>

class CarWash
{
public:
    CarWash(CSV &st, CSV &wo);
    void pass_time(unsigned int t);
    void do_commands();
    void add_car();
    void print_timeline(vector<Event> &timeline);
    ~CarWash();

private:
    map<unsigned int, Stage *> stages;
    map<unsigned int, Worker *> workers;
    unsigned int time;
    map<unsigned int, Car *> cars;
};

#endif