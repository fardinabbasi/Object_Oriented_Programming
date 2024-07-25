#include "interface.hpp"
#include "defs.hpp"
#include "utms.hpp"

int main(int argc, char *argv[])
{
    if (argc < ARGS_NUM)
    {
        cerr << ARGS_FAILED_MESSAGE << endl;
        return 1;
    }
    map<string, string> files_path;

    files_path["majors"] = argv[MAJORS_FILE_INDEX];
    files_path["students"] = argv[STUDENTS_FILE_INDEX];
    files_path["courses"] = argv[COURSES_FILE_INDEX];
    files_path["profs"] = argv[PROFS_FILE_INDEX];

    UTMS sys = UTMS(files_path);
    sys.read_commands();
    Interface::del_instance();
    return 0;
}