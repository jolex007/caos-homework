#include <fstream>
#include <iostream>
#include <string>

extern "C" {
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
}

int main(int argc, char* argv[])
{
    signal(SIGPIPE, SIG_IGN);

    using std::cin;
    using std::cout;
    using std::endl;
    using std::ifstream;
    using std::ofstream;
    using std::stoi;

    ifstream in(argv[1]);
    int initial_value;
    in >> initial_value;
    cout << initial_value << endl;

    pid_t printed_pid = -1;
    cin >> printed_pid;

    int action = 0;
    int value = 0;
    while (!in.eof()) {
        in >> action;
        if (0 == action)
            break;
        else if (1 == action) {
            kill(printed_pid, SIGUSR1);
            usleep(100000);
        } else if (2 == action) {
            kill(printed_pid, SIGUSR2);
            usleep(100000);
        }
        cin >> value;
        cout << value << " ";
    }
    kill(printed_pid, SIGTERM);
    waitpid(printed_pid, NULL, 0);
    return 0;
}
