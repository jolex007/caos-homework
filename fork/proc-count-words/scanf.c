#include <sys/types.h>
#include <unistd.h>

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static pid_t last_used_pid = 0;
static char buffer[4096];

__attribute__((constructor))
void initialize_scanf_buffer()
{
    memset(buffer, 0, sizeof(buffer));
    if (0 != setvbuf(stdin, buffer, _IOFBF, sizeof(buffer))) {
        perror("setvbuf");
    }
    else {
        fprintf(stderr, "Set buffer to size of %d\n", (int) sizeof(buffer));
    }
}


int __real___isoc99_scanf(const char *format, ...);
int __wrap___isoc99_scanf(const char *format, ...)
{
    pid_t my_pid = getpid();
    if (last_used_pid == my_pid) {
        printf("Scanf used more then once in this process!\n");
        return 0;
    }
    else {
        int result;
        va_list args;
        va_start(args, format);
        result = vscanf(format, args);
        va_end(args);
        last_used_pid = my_pid;
        return result;
    }
}
