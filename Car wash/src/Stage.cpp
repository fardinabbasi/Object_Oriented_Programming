#include "stage.hpp"

void Stage::modify_car_line(Car *car, string mode)
{
    line_cars[car] = mode;
}

void Stage::add_worker(Worker *worker)
{
    line_workers.push_back(worker);
}

optional<Worker *> Stage::find_worker(Car *car)
{
    optional<Worker *> best_worker;

    for (auto &[line_car, mode] : line_cars)
    {
        if (mode == CAR_IN_QUEUE && line_car->get_id() < car->get_id())
        {
            return best_worker;
        }
    }

    sort(line_workers.begin(), line_workers.end(), [](Worker *w1, Worker *w2)
         {
        if(w1->get_finish_time() == w2->get_finish_time())
            return w1->get_id() < w2->get_id();
        else   
            return w1->get_finish_time() < w2->get_finish_time(); });

    auto it = find_if(line_workers.begin(), line_workers.end(), [](Worker *w)
                      { return w->get_status() == WORKER_IDLE; });

    if (it != line_workers.end())
        best_worker = *it;
    return best_worker;
}

void Stage::print_status()
{
    unsigned int washed_cars = 0, in_queue_cars = 0, being_washed = 0;

    for (auto &[_, mode] : line_cars)
    {
        if (mode == CAR_WASHED)
            washed_cars += 1;
        else if (mode == CAR_BEING_WASHED)
            being_washed += 1;
        else
            in_queue_cars += 1;
    }

    cout << WASHED_CARS_REPORT << washed_cars << endl;
    cout << CARS_IN_QUEUE_REPORT << in_queue_cars << endl;
    cout << CARS_BEING_WASHED_REPORT << being_washed << endl;
    cout << INCOME_REPORT << washed_cars * price << endl;
}