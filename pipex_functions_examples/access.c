#include <unistd.h>
#include <stdio.h>

int is_executable(char *file_path)
{
	if (access(file_path, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		if (is_executable(av[1]))
			printf("✅ This file '%s' is executable!", av[1]);
		else
			printf("❌ This file '%s' is NOT executable.", av[1]);
	}
	else
		printf("(!) Please pass a file path as an arg");
	printf("\n");
}