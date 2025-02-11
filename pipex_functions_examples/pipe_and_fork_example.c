#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{
	int array[] = {1, 1, 2, 3, 1, 2};
	int arraySize = sizeof(array) / sizeof(int);
	int fd[2];
	int start;
	int end;

	if (pipe(fd) < 0)
	{
		printf("Error creating pipe\n");
		return (1);
	}
	int id = fork();
	if (id < 0)
	{
		printf("Error when forking\n");
		return (1);
	}
	int is_child_p = (id == 0) ? 1 : 0;
	if (is_child_p)
	{
		// inside child process:
		start = 0;
		end = arraySize / 2;
	}
	else {
		// inside parent process:
		start = arraySize / 2;
		end = arraySize;
	}
	int sum = 0;
	while (start < end)
	{
		sum += array[start];
		start++;
	}
	printf("Sum: %d\n", sum);
	if (is_child_p)
	{
		// send sum to parent
		close(fd[0]);
		write(fd[1], &sum, sizeof(int));
		close(fd[1]);
	}
	else {
		int total;
		close(fd[1]);
		read(fd[0], &total, sizeof(int));
		close(fd[0]);
		total += sum;
		printf("Total sum is : %d\n", total);
	}
}