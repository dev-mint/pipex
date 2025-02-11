#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	int old_fd = open("example.txt", O_RDWR);
	if (old_fd < 0)
	{
		printf("Cannot Open File\n");
		return (1);
	}
	printf("old_fd = %d\n", old_fd);
	int new_fd = 12;
	if (dup2(old_fd, new_fd) == -1)
	{
        perror("dup2 failed");
        close(old_fd);
        return 1;
    }
	
	printf("new_fd = %d\n", new_fd);
	write(old_fd, "dup2: using old fd\n", 19);
	write(new_fd, "dup2: using new fd\n", 19);
	
	close(old_fd);
	close(new_fd);
	return (0);
}