#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <optional>

using namespace std;

class Event{
    public:
    Event(unsigned int time, unsigned int car_id, pair<string, unsigned int> prev_pos, pair<string, optional<unsigned int>> curr_pos):
    time(time), car_id(car_id), prev_pos(prev_pos), curr_pos(curr_pos){}
    void print();
    bool operator<(const Event& other) const{
        if(time == other.time)
            return car_id < other.car_id;
        else
            return time < other.time;
    }
    private:
    unsigned int time;
    unsigned int car_id;
    pair<string, unsigned int> prev_pos;
    pair<string, optional<unsigned int>> curr_pos;
};

#endif