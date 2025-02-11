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
	int new_fd = dup(old_fd);
	
	if (new_fd < 0)  // Always good to check if dup worked
    {
        printf("dup failed\n");
        close(old_fd); // Make sure to close the old_fd if dup fails
        return (1);
    }
	
	printf("new_fd = %d\n", new_fd);
	write(old_fd, "using old fd\n", 13);
	write(new_fd, "using new fd\n", 13);
	
	close(old_fd);
	close(new_fd);
	return (0);
}