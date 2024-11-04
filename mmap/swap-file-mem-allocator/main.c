#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <linux/limits.h>
#include <unistd.h>

extern void
myalloc_initialize(int fd);

extern void
myalloc_finalize();

extern void*
my_malloc(size_t size);

extern void
my_free(void *ptr);

typedef enum op_type {
    Initialize,
    Finalize,
    Malloc,
    Free,
    Fill,
    Ensure
} op_type_t;

typedef struct operation {
    op_type_t   type;
    int         pointer_id;
    size_t      size;
    bool        expects_error;
    char        fill_char;
    char        file_name[PATH_MAX];
} operation_t;

static operation_t
parse_next_line(char *buffer)
{
    operation_t result;
    char minibuf[20];
    memset(&result, 0 ,sizeof(result));
    memset(minibuf, 0, sizeof(minibuf));
    if (3==sscanf(buffer, "malloc %d %ld %s", &result.pointer_id, &result.size, minibuf)) {
        if (0==strncmp(minibuf, "ERROR", sizeof(minibuf))) {
            result.expects_error = true;
        }
        result.type = Malloc;
    }
    else if (1==sscanf(buffer, "free %d", &result.pointer_id)) {
        result.type = Free;
    }
    else if (2==sscanf(buffer, "initialize %s %ld", result.file_name, &result.size)) {
        result.type = Initialize;
    }
    else if (buffer==strstr(buffer, "finalize")) {
        result.type = Finalize;
    }
    else if (3==sscanf(buffer, "fill %d %ld %s", &result.pointer_id, &result.size, minibuf)) {
        result.type = Fill;
        result.fill_char = minibuf[0];
    }
    else if (3==sscanf(buffer, "ensure %d %ld %s", &result.pointer_id, &result.size, minibuf)) {
        result.type = Ensure;
        result.fill_char = minibuf[0];
    }
    else {
        fprintf(stderr, "Can't parse input line: %s\n", buffer);
        exit(5);
    }
    return result;
}

static char * g_ids[1000];
static int g_fd = 0;

static void
process_operation(operation_t op)
{
    switch (op.type) {
        case Initialize:
            g_fd = open(op.file_name, O_RDWR|O_CREAT|O_TRUNC, 0640);
            ftruncate(g_fd, op.size);
            myalloc_initialize(g_fd);
            break;
        case Finalize:
            myalloc_finalize();
            break;
        case Malloc:
            g_ids[op.pointer_id] = my_malloc(op.size);
            if (g_ids[op.pointer_id] && op.expects_error) {
                fprintf(stdout, "Expected error on my_malloc(%ld)\n", op.size);
                exit(1);
            }
            else if (NULL==g_ids[op.pointer_id] && !op.expects_error) {
                fprintf(stdout, "Can't allocate %ld bytes\n", op.size);
                exit(1);
            }
            break;
        case Free:
            my_free(g_ids[op.pointer_id]);
            break;
        case Fill:
            memset(g_ids[op.pointer_id], op.fill_char, op.size);
            break;
        case Ensure:
            for (size_t i = 0; i < op.size; ++i) {
                if (g_ids[op.pointer_id][i]!=op.fill_char) {
                    fprintf(stdout, "Data broken on pointer with id %d\n", op.pointer_id);
                    exit(1);
                }
            }
            break;
    }
}

int main(int argc, char *argv[])
{
    FILE* in = argc > 1 ? fopen(argv[1], "r") : stdin;
    char buffer[200];
    memset(buffer, 0, sizeof(buffer));

    while (fgets(buffer, sizeof(buffer), in)) {
        if ('#'!=buffer[0]) {
            operation_t op = parse_next_line(buffer);
            process_operation(op);
        }
    }
}
