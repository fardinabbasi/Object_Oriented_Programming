#include "utils.hpp"
#include "Stage.hpp"
#include "Worker.hpp"
#include "Defs.hpp"
#include "CarWash.hpp"
#include <string>
#include <map>

using namespace std;

int main(int argc, char* argv[]){
    const string stages_file_path = argv[STAGES_FILE_INDEX];
    const string workers_file_path = argv[WORKERS_FILE_INDEX];
    map<unsigned int, Stage*> stages = read_stages(stages_file_path);
    map<unsigned int, Worker*> workers = read_workers(workers_file_path);
    CarWash carwash(stages, workers);

    carwash.do_commands();

    return 0;
}