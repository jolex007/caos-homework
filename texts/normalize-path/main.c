#include <stdio.h>
#include <limits.h>
#include <linux/limits.h>

extern void
normalize_path(char * path);

void main()
{
    char buffer[PATH_MAX];
    while (scanf("%s", buffer)>0) {
        normalize_path(buffer);
        printf("%s", buffer);
    }
}
