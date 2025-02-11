#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	if (unlink("test.txt") != 0)
	{
		printf("Error deleting the file\n");
		return (1);
	}
	// (!) even after deleting the file if there is
	// still an fd related to that file open, then you still
	// can access its data until its closed.
	printf("File deleted successfully\n");
	return (0);
}