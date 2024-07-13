#ifndef DEFS_HPP
#define DEFS_HPP

#include <map>
#include <list>
#include <string>

using namespace std;
typedef list<map<string, unsigned int>> CSV;

#define STAGES_FILE_INDEX 1
#define WORKERS_FILE_INDEX 2
#define TIME_UNIT 1
#define CAR_DONE "Done"
#define CAR_IN_SERVICE "In service"
#define CAR_IN_LINE "In line"
#define WORKER_IDLE "Idle"
#define CAR_WASHED "washed"
#define CAR_IN_QUEUE "in_queue"
#define CAR_BEING_WASHED "being_washed"
#define ARRIVED_MESSAGE ": Arrived -> "
#define NOT_FOUND_MESSAGE "NOT FOUND"
#define FILE_FAILED_MESSAGE "Failed to open the file!"
#define PASS_TIME_COMMAND "pass_time"
#define CAR_ARRIVAL_COMMAND "car_arrival"
#define STAGE_STATUS_COMMAND "get_stage_status"
#define WORKER_STATUS_COMMAND "get_worker_status"
#define CAR_STATUS_COMMAND "get_car_status"
#define WRONG_COMMAND_MESSAGE "Not supported Command"
#define WASHED_CARS_REPORT "Number of washed cars: "
#define CARS_IN_QUEUE_REPORT "Number of cars in queue: "
#define CARS_BEING_WASHED_REPORT "Number of cars being washed: "
#define INCOME_REPORT "Income: "

#endif