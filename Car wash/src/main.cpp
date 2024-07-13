#include "defs.hpp"
#include "utils.hpp"
#include "carwash.hpp"

int main(int argc, char *argv[])
{
    const string stages_file_path = argv[STAGES_FILE_INDEX];
    const string workers_file_path = argv[WORKERS_FILE_INDEX];
    CSV stages = read_csv(stages_file_path);
    CSV workers = read_csv(workers_file_path);
    CarWash carwash(stages, workers);

    carwash.do_commands();

    return 0;
}