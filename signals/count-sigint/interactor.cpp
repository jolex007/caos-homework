#include <fstream>
#include <iostream>
#include <string>

extern "C" {
    #include <sys/types.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <unistd.h>
}

int main(int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    
    using std::ifstream;
    using std::ofstream;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::stoi;

    ifstream in(argv[1]);
    int sigint_count;
    in >> sigint_count;

    pid_t printed_pid = -1;
    cin >> printed_pid;
    
    for (int i=0; i<sigint_count; ++i) {
        kill(printed_pid, SIGINT);
        usleep(100000);
    }
    kill(printed_pid, SIGTERM);
    int result = 0;
    cin >> result;
    waitpid(printed_pid, NULL, 0);
    cout << result;
    return 0;
}
