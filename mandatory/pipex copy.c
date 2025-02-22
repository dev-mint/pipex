/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:49:00 by anachat           #+#    #+#             */
/*   Updated: 2025/02/22 15:41:08 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parent(char **av, char **env)
{
	char *path;
	char **cmd;
	int fd[3];
	int id;
	int f;
	
	f = open(av[1],O_RDONLY);
	if (f < 0)
		return (0);
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		return 0;
	path = get_path(cmd[0], get_env_path(env));
	if (!path)
		return 0;
	if (pipe(fd) < 0)
		return 0;
	fd[2] = f;
	id = fork();
	if (id < 0)
		return (0);
	if (id == 0)
	{
		dup2(f,0);
		close(f);
		dup2(fd[1],1);
		close(fd[1]);
		if (execve(path, cmd, env) != -1)
		{
			return (0);
		}
	}
	else
	{
		dup2(fd[0],0);
		close(fd[0]);
	}
	return (0);
}

int	parent2(char **av, char **env)
{
	char *path;
	char **cmd;
	int id;

	int fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_out < 0)
		return (1);
	cmd = ft_split(av[3], ' ');
	if (!cmd)
		return (1);
	path = get_path(cmd[0], get_env_path(env));
	if (!path)
		return (1);
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		dup2(fd_out, 1);
		if (execve(path, cmd, env) != -1)
		{
			return (0);
		}
	}
	return (0);
}

	
int	main(int ac, char **av,char **env)
{
	if (ac != 5)
		return (0);
	parent(av,env);
	parent2(av,env);

	return (0);
}
