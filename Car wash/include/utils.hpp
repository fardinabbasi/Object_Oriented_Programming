#ifndef UTILS_CPP
#define UTILS_CPP

#include "Stage.hpp"
#include "Worker.hpp"
#include "Defs.hpp"
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

const char COMMA_DELIM = ',';

string trim(const string str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (start == std::string::npos)
        return "";
    else
        return str.substr(start, end - start + 1);
}

map<unsigned int, Stage*> read_stages(const string path){
    ifstream fin(path);
    if (!fin.is_open()) {
        cerr << FILE_FAILED_MESSAGE << endl;
    }
    map<unsigned int, Stage*> stages;
    string line, id, price;
    getline(fin, line);

    while(getline(fin, line)){
        stringstream ss(line);
        getline(ss, id, COMMA_DELIM);
        getline(ss, price, COMMA_DELIM);
        id = trim(id);
        price = trim(price);
        stages[stoul(id)] = new Stage(stoul(id), stoul(price));
    }
    fin.close();
    return stages;
}

map<unsigned int, Worker*> read_workers(const string path){
    ifstream fin(path);
    if (!fin.is_open()) {
        cerr << FILE_FAILED_MESSAGE << endl;
    }
    map<unsigned int, Worker*> workers;
    string line, id, stage_id, finish_time;
    getline(fin, line);

    while(getline(fin, line)){
        stringstream ss(line);
        getline(ss, id, COMMA_DELIM);
        getline(ss, stage_id, COMMA_DELIM);
        getline(ss, finish_time, COMMA_DELIM);
        id = trim(id);
        stage_id = trim(stage_id);
        finish_time = trim(finish_time);
        workers[stoul(id)] = new Worker(stoul(id), stoul(stage_id), stoul(finish_time));
    }
    fin.close();
    return workers;
}

#endif