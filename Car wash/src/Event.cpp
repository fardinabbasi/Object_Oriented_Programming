#include <iostream>
#include "Event.hpp"

using namespace std;

void Event::print(){
    cout << time << " Car " << car_id << ": " << prev_pos.first << " " << prev_pos.second << " -> " 
    << curr_pos.first << (curr_pos.second.has_value()? " " + to_string(curr_pos.second.value()): "") << endl;
}