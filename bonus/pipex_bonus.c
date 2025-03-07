/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:49:00 by anachat           #+#    #+#             */
/*   Updated: 2025/03/07 18:03:08 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		// ft_dup2(fd[2], 0);
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
	{
		return (close(fd[1]), ft_dup2(fd[0], 0), 0);
	}
}

static int	parent(int *fd, char **av, int i, char **env)
{
	char	**cmd;
	char	*path;

	if (pipe(fd) < 0)
		return (perror("pipe failed"), 1);
	// fd[2] = open(av[1], O_RDONLY);
	// if (fd[2] < 0)
	// 	return (perror("failed to open infile"), close(fd[1]), ft_dup2(fd[0], 0), 1);
	int res = file_check(av, i);
	printf(RED "===> response: %d\n" RESET, res);
	if (res != 0)
		return (0);
	cmd = ft_split(av[i], ' ');
	if (!cmd)
		return (perror("allocation error"), close(fd[1]), close(fd[2]), ft_dup2(fd[0], 0), 1);
	path = get_path(cmd[0], env);
	if (!path)
	{
		perror("cannot find cmd path");
		return (free_arr(cmd), close(fd[1]), close(fd[2]), ft_dup2(fd[0], 0), 1);
	}
	exec_child1(fd, path, cmd, env);
	return (free_arr(cmd), close(fd[1]), close(fd[0]), free(path), 0);
}

static int	parent2(int *fd, char **av, int i, char **env)
{
	int		out_fd;
	char	*path;
	char	**cmd;
	int		id;

	out_fd = open(av[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (out_fd < 0)
		return (perror("error opening outfile"), 1);
	cmd = ft_split(av[i], ' ');
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
		ft_close2(fd[0], fd[1]);
		check_fds_in_child("<<<< Child 2 >>>>>>");
		if (execve(path, cmd, env) == -1)
			return (perror("execve 2 failed"), free_arr(cmd), free(path), check_fds_in_child("<<<< Child 3 >>>>>>"), exit(1), 1);
	}
	return (free_arr(cmd), free(path), close(out_fd), 0);
}

int	main(int ac, char **av, char **env)
{
	int	fd[7];
	int	i;

	fd[3] = dup(0);
	fd[4] = dup(1);
	if (ac < 5)
		return (0);
	i = 2;
	if (is_heredoc(av[1]))
	{
		if (ac < 6)
			return (perror("Invalid args number for her_doc"), 0);
		i++;
	}
	while (i < ac - 2)
	{
		parent(fd, av, i, env);
		i++;
	}
	parent2(fd, av, i, env);
	ft_dup2(fd[3], 0);
	ft_dup2(fd[4], 1);
	// check_fds_in_child("<<<<<< Parent >>>>>>");
	while (wait(0) != -1)
		;
	return (0);
}
