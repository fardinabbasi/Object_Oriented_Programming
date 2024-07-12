#ifndef CAR_HPP
#define CAR_HPP

#include "Stage.hpp"
#include "Worker.hpp"
#include "Event.hpp"
#include <list>
#include <string>
#include <optional>

using namespace std;
class Stage;

class Car{
    public:
    Car(unsigned int id, unsigned int time, list<Stage*> q);
    bool set_worker();
    unsigned int get_id() const{ return car_id; }
    unsigned int curr_stage_id();
    string get_status(bool print_mode=false);
    optional<Event> pass_time(unsigned int t);
    void add_car_notif();

    private:
    unsigned int car_id;
    unsigned int time;
    list<Stage*> queue;
    optional<Worker*> worker;
};

#endif