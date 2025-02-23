/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:49:00 by anachat           #+#    #+#             */
/*   Updated: 2025/02/23 11:57:13 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_process(char **av, char **env, int *fd, char ***cmd)
{
	char	*path;
	int		in_fd;

	in_fd = open(av[1], O_RDONLY);
	if (in_fd < 0)
		return (perror("failed to open infile\n"), -1);
	*cmd = ft_split(av[2], ' ');
	if (!*cmd)
		return (perror("allocation error\n"), -1);
	path = get_path((*cmd)[0], env);
	if (!path)
		return (perror("cannot find cmd path\n"), -1);
	if (pipe(fd) < 0)
		return (perror("pipe failed\n"), -1);
	return (in_fd);
}

static int	parent(char **av, char **env)
{
	char	**cmd;
	int		fd[3];
	int		id;

	fd[2] = init_process(av, env, fd, &cmd);
	if (fd[2] == -1)
		return (1);
	id = fork();
	if (id < 0)
		return (perror("fork failed\n"), 1);
	if (id == 0)
	{
		ft_dup2(fd[2], 0);
		ft_dup2(fd[1], 1);
		if (execve(get_path(cmd[0], env), cmd, env) == -1)
			return (perror("execve 1 failed\n"), exit(1), 1);
	}
	else
		return (ft_dup2(fd[0], 0), close(fd[1]), 0);
	return (0);
}

static int	parent2(char **av, char **env)
{
	char	*path;
	char	**cmd;
	int		out_fd;
	int		id;

	out_fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (out_fd < 0)
		return (perror("error opening outfile"), exit(1), 1);
	cmd = ft_split(av[3], ' ');
	if (!cmd)
		return (1);
	path = get_path(cmd[0], env);
	if (!path)
		return (1);
	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
	{
		ft_dup2(out_fd, 1);
		if (execve(path, cmd, env) == -1)
			return (perror("execve 2 failed"), exit(1), 1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
		return (0);
	parent(av, env);
	parent2(av, env);
	while (wait(0) != -1)
		;
	return (0);
}
