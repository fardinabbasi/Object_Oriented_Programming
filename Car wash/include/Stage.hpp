#ifndef STAGE_HPP
#define STAGE_HPP

#include "defs.hpp"
#include "worker.hpp"
#include "car.hpp"
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <iostream>
#include <algorithm>

class Car;

class Stage
{
public:
    Stage() {}
    Stage(map<string, unsigned int> info) : id(info["Id"]), price(info["Price"]) {}
    unsigned int get_id() const { return id; }
    unsigned int get_price() const { return price; }
    void add_worker(Worker *worker);
    optional<Worker *> find_worker(Car *car);
    void print_status();
    void modify_car_line(Car *car, string mode);

private:
    unsigned int id;
    unsigned int price;
    map<Car *, string> line_cars;
    vector<Worker *> line_workers;
};

#endif