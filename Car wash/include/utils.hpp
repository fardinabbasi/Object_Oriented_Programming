#ifndef UTILS_CPP
#define UTILS_CPP

#include "defs.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

const char CSV_DELIM = ',';

string trim(const string str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (start == std::string::npos)
        return "";
    else
        return str.substr(start, end - start + 1);
}

CSV read_csv(const string path)
{
    ifstream fin(path);
    if (!fin.is_open())
    {
        cerr << FILE_FAILED_MESSAGE << endl;
    }
    CSV info;
    list<string> keys;
    string line, value;
    map<string, unsigned int> row;

    getline(fin, line);
    line = trim(line);
    stringstream ss(line);
    while (getline(ss, value, CSV_DELIM))
    {
        keys.push_back(value);
    }
    while (getline(fin, line))
    {
        row.clear();
        line = trim(line);
        stringstream ss(line);
        auto it = keys.begin();
        while (getline(ss, value, CSV_DELIM))
        {
            if (!value.empty())
            {
                row[*it] = stoul(value);
            }
            it++;
        }
        info.push_back(row);
    }
    fin.close();
    return info;
}

#endif