
#include "pipex_bonus.h"




#define GREEN  "\033[1;32m"
#define RED    "\033[1;31m"
#define RESET  "\033[0m"

void check_fd_status(int fd, const char *name)
{
    if (fcntl(fd, F_GETFD) != -1)
        printf(GREEN "[✔] FD %d (%s) is open\n" RESET, fd, name);
    else
        printf(RED "[✘] FD %d (%s) is closed\n" RESET, fd, name);
}
void	f(void)
{
	// system("leaks pipex");// Check for memory leaks
	system("lsof | grep '^pipex'"); // Check for open file descriptors
}

void	check_fds_in_child(const char *msg)
{
	pid_t pid = getpid();
	char cmd[256];

	dprintf(2, "\033[38;5;226m" "%s (PID: %d)\n" "\033[0m", msg, pid);  // Print to stderr instead of stdout
	snprintf(cmd, sizeof(cmd), "lsof -p %d >&2", pid); // Redirect output to stderr
	system(cmd);
}

static int	exec_child1(int *fd, char *path, char **cmd, char **env)
{
	int	id;

	id = fork();
	if (id < 0)
		return (perror("fork failed"), ft_dup2(fd[0], 0), 1);
	if (id == 0)
	{
		close(fd[3]);
		close(fd[4]);
		ft_dup2(fd[2], 0);
		close(fd[0]);
		ft_dup2(fd[1], 1);
		// check_fds_in_child("<<<< Child 1 >>>>>>");
		if (execve(path, cmd, env) == -1)
		{
			perror("execve 1 failed");
			exit(1);
		}
		return (0);
	}
	else
		return (ft_dup2(fd[0], 0), close(fd[2]), 0);
}

static int	parent(int *fd,  char *cmd_arg, char *infile, char **env)
{
	char	**cmd;
	char	*path;

	if (pipe(fd) < 0)
		return (perror("pipe failed"), 1);
	fd[2] = open(infile, O_RDONLY);
	if (fd[2] < 0)
		return (perror("failed to open infile"), ft_dup2(fd[0], 0), 1);
	cmd = ft_split(cmd_arg, ' ');
	if (!cmd)
		return (perror("allocation error"), close(fd[2]), ft_dup2(fd[0], 0), 1);
	path = get_path(cmd[0], env);
	if (!path)
	{
		perror("cannot find cmd path");
		return (free_arr(cmd), close(fd[2]), ft_dup2(fd[0], 0), 1);
	}
	exec_child1(fd, path, cmd, env);
	return (free_arr(cmd), ft_dup2(fd[0], 0),ft_dup2(fd[1], fd[1]), close(fd[2]), free(path), 0);
}

static int	parent2(int *fd, char *cmd_arg, char *outfile, char **env)
{
	int		out_fd;
	char	*path;
	char	**cmd;
	int		id;

	out_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (out_fd < 0)
		return (perror("error opening outfile"), 1);		
	cmd = ft_split(cmd_arg, ' ');
	if (!cmd)
		return (close(out_fd), 1);
	path = get_path(cmd[0], env);
	if (!path)
		return (free_arr(cmd), close(out_fd), 1);
	id = fork();
	if (id < 0)
		return (close(out_fd), 1);
	if (id == 0)
	{
		ft_close2(fd[3], fd[4]);
		ft_dup2(out_fd, 1);
		// check_fds_in_child("<<<< Child 2 >>>>>>");
		if (execve(path, cmd, env) == -1)
			return (perror("execve 2 failed"), free_arr(cmd), free(path), exit(1), 1);
	}
	return (free_arr(cmd), free(path), close(out_fd), 0);
}




static int	exec_child3(int *fd, char *path, char **cmd, char **env)
{
	int	id;

	id = fork();
	if (id < 0)
		return (perror("fork failed"), ft_dup2(fd[0], 0), 1);
	if (id == 0)
	{
		close(fd[3]);
		close(fd[4]);
		check_fds_in_child("<<<< Middle Child >>>>>>");
		if (execve(path, cmd, env) == -1)
		{
			perror("execve 1 failed");
			exit(1);
		}
		return (0);
	}
	else
		return (0);
}


static int	middle(int *fd, char *cmd_arg, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(cmd_arg, ' ');
	if (!cmd)
		return (perror("allocation error"), close(fd[1]), ft_dup2(fd[0], 0), 1);
	path = get_path(cmd[0], env);
	if (!path)
	{
		perror("cannot find cmd path");
		return (free_arr(cmd), close(fd[1]), ft_dup2(fd[0], 0), 1);
	}
	exec_child3(fd, path, cmd, env);
	return (free_arr(cmd), free(path), 0);
}

int	main(int ac, char **av, char **env)
{
	int	fd[7];
	int	i;

	fd[3] = dup(0);
	fd[4] = dup(1);
	if (ac < 5)
		return (0);
		
	parent(fd, av[2], av[1], env);
	i = 3;
	while (i < ac)
	{
		if ((i + 2) < ac)
			middle(fd, av[i], env);
		else
		{
			printf("\n===========> cmd_arg: %s, outfile: %s\n", av[ac - 2], av[ac - 1]);
			(void)parent2;
			parent2(fd, av[ac - 2], av[ac - 1], env);
			break ;
		}
		i++;
	}
	ft_dup2(fd[3], 0);
	ft_dup2(fd[4], 1);
	// check_fds_in_child("<  <<< Parent >>>>>>");
	while (wait(0) != -1)
		;
	return (0);
}