#include <iostream>
#include "Car.hpp"
#include "Defs.hpp"

using namespace std;

Car::Car(unsigned int id, unsigned int time, list<Stage*> q): car_id(id), time(time), queue(q){
        for(auto stage: queue){
            stage->modify_car_line(this, CAR_IN_QUEUE);
        }
        if(set_worker())
            queue.front()->modify_car_line(this, CAR_BEING_WASHED);
    }

bool Car::set_worker(){
    auto curr_stage = queue.front();
    auto finded_worker = curr_stage->find_worker(this);
    if (finded_worker.has_value()){
        worker = finded_worker.value();
        worker.value()->do_job(car_id);
        return true;
    }
    else
        return false;
}

void Car::add_car_notif(){
    string mode = (get_status() == CAR_IN_SERVICE ? "Stage ": "Queue ");
    cout << time  << " Car " << car_id << ARRIVED_MESSAGE << mode << curr_stage_id() << endl;
}

optional<Event> Car::pass_time(unsigned int t){
    optional<Event> event;
    pair<string, unsigned int> prev_pos;
    pair<string, optional<unsigned int>> curr_pos;
    Stage* curr_stage = queue.front();
    time += t;
    if (get_status() != CAR_DONE){
        if (worker.has_value()){
            if(worker.value()->get_status() == WORKER_IDLE){
                curr_stage->modify_car_line(this, CAR_WASHED);
                prev_pos = make_pair("Stage", curr_stage_id());
                worker.reset();
                queue.pop_front();

                if(get_status() == CAR_DONE){
                    curr_pos = make_pair(CAR_DONE, nullopt);
                }
                else{
                    curr_stage = queue.front();
                    curr_stage->modify_car_line(this, CAR_IN_QUEUE);
                    if(set_worker()){
                        curr_stage->modify_car_line(this, CAR_BEING_WASHED);
                        curr_pos = make_pair("Stage", curr_stage_id());
                    }
                    else{
                        curr_pos = make_pair("Queue", curr_stage_id());
                    }
                }
                event = Event(time, car_id, prev_pos, curr_pos);
            }
        }
        else{
            if(set_worker()){
                curr_stage->modify_car_line(this, CAR_BEING_WASHED);
                prev_pos = make_pair("Queue", curr_stage_id());
                curr_pos = make_pair("Stage", curr_stage_id());
                event = Event(time, car_id, prev_pos, curr_pos);
            }
        }
    }
    return event;
}

string Car::get_status(bool print_mode){
    string status;
    if(queue.empty())
        status = CAR_DONE;
    else{
        if(worker.has_value())
            status = CAR_IN_SERVICE;
        else
            status = CAR_IN_LINE;
    }
    if(print_mode){
        cout << status;
        if(status != CAR_DONE)
            cout << ": " << curr_stage_id();
        cout << endl;
    }
    return status;
}

unsigned int Car::curr_stage_id(){ 
    return queue.front()->get_id(); 
}