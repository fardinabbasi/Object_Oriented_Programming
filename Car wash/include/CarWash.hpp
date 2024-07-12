#ifndef CARWASH_HPP
#define CARWASH_HPP

#include "Stage.hpp"
#include "Worker.hpp"
#include "Event.hpp"
#include "Car.hpp"
#include <map>
#include <vector>


using namespace std;

class CarWash{
    public:
    CarWash(map<unsigned int, Stage*> st, map<unsigned int, Worker*> wo);
    void pass_time(unsigned int t);
    void do_commands();
    void add_car();
    void print_timeline(vector<Event>& timeline);
    ~CarWash();

    private:
    map<unsigned int, Stage*> stages;
    map<unsigned int, Worker*> workers;
    unsigned int time;
    map<unsigned int, Car*> cars;
};

#endif