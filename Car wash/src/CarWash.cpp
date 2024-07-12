#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>
#include "CarWash.hpp"
#include "Defs.hpp"

using namespace std;

CarWash::CarWash(map<unsigned int, Stage*> st, map<unsigned int, Worker*> wo): stages(st), workers(wo) { 
    time = 0;
    for (auto& [_, worker]: workers){
        stages[worker->get_stage()]->add_worker(worker);
    } 
}

void CarWash::print_timeline(vector<Event>& timeline){
    if(!timeline.empty())
        sort(timeline.begin(), timeline.end());
    for (Event& event: timeline){
        event.print();
    }
}

void CarWash::pass_time(unsigned int t){
    vector<Event> timeline;
    optional<Event> event;
    while(t > 0){
        time += TIME_UNIT;
        for (auto& [_, worker]: workers){
            worker->pass_time(TIME_UNIT);
        }
        for (auto& [_, car]: cars){
            event = car->pass_time(TIME_UNIT);
            if(event.has_value())
                timeline.push_back(event.value());
        }
        t -= TIME_UNIT;
        print_timeline(timeline);
        timeline.clear();
    }
}

void CarWash::add_car(){
    string line, mode;
    unsigned int stage_id, car_id;
    getline(cin, line);
    stringstream ss(line);
    list<Stage*> queue;
    car_id = cars.size() + 1;
    while(ss >> stage_id){
        auto it = find_if(stages.begin(), stages.end(), [stage_id](const auto& pair) {
        return pair.first == stage_id;});
        queue.push_back(it->second);
    }
    cars[car_id] = new Car(car_id, time, queue);
    cars[car_id]->add_car_notif();
}

void CarWash::do_commands(){
    string command, status;
    unsigned int num;

    while(cin >> command){
        if (command == PASS_TIME_COMMAND){
            cin >> num;
            pass_time(num);
        }
        else if (command == CAR_ARRIVAL_COMMAND){
            add_car();
        }
        else if (command == STAGE_STATUS_COMMAND){
            cin >> num;
            if (stages.find(num) == stages.end())
                cout << NOT_FOUND_MESSAGE << endl;
            else
                stages[num]->print_status();
        }
        else if (command == WORKER_STATUS_COMMAND){
            cin >> num;
            if (workers.find(num) == workers.end())
                cout << NOT_FOUND_MESSAGE << endl;
            else
                workers[num]->get_status(true);
        }
        else if (command == CAR_STATUS_COMMAND){
            cin >> num;
            if (cars.find(num) == cars.end())
                cout << NOT_FOUND_MESSAGE << endl;
            else
                cars[num]->get_status(true);
        }
        else{
            cerr << WRONG_COMMAND_MESSAGE << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

CarWash::~CarWash() {
    for (auto& stage : stages) {
        delete stage.second;
    }
    stages.clear();

    for (auto& worker : workers) {
        delete worker.second;
    }
    workers.clear(); 

    for (auto& car : cars) {
        delete car.second;
    }
    cars.clear();
}