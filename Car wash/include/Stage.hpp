#ifndef STAGE_HPP
#define STAGE_HPP

#include "Worker.hpp"
#include "Car.hpp"
#include <string>
#include <vector>
#include <map>
#include <optional>

using namespace std;

class Car;

class Stage{
    public:
    Stage(){}
    Stage(const unsigned int id, const unsigned int price): id(id), price(price){}
    unsigned int get_id() const{ return id; }
    unsigned int get_price() const{ return price; }
    void add_worker(Worker* worker);
    optional<Worker*> find_worker(Car* car);
    void print_status();
    void modify_car_line(Car* car, string mode);

    private:
    unsigned int id;
    unsigned int price;
    map<Car*, string> line_cars;
    vector<Worker*> line_workers;
};

#endif