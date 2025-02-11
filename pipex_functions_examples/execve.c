#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
    char *args[] = {"/bin/ls", "-l", NULL};
    char *env[] = {NULL}; // No custom environment variables

    if (execve("/bin/ls", args, NULL) == -1) {
        perror("execve failed");
        return 1;
    }

    // This line won't be reached because execve replaces the current process
    return 0;
}