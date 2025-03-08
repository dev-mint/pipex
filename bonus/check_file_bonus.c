/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:18:31 by anachat           #+#    #+#             */
/*   Updated: 2025/03/08 13:23:18 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_heredoc(char *arg)
{
	if (ft_strncmp("here_doc", arg, 9) == 0)
		return (1);
	return (0);
}

static int	write_input(char *end)
{
	char	*line;
	int		len;
	int		heredoc_fd;

	heredoc_fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (heredoc_fd < 0)
		return (perror("cannot open here_doc file"), -1);
	line = get_next_line(0);
	if (!line)
		return (ft_dup2(heredoc_fd, 0), -1);
	while (line)
	{
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (ft_strncmp(line, end, ft_strlen(end) + 1) == 0)
			break ;
		line[len - 1] = '\n';
		ft_putstr_fd(line, heredoc_fd);
		free(line);
		line = get_next_line(0);
	}
	return (close(heredoc_fd), free(line), 0);
}

int	file_check(char **av, int i, int *fd)
{
	int	infile;
	int	res;

	if (is_heredoc(av[1]) && i == 3)
	{
		res = write_input(av[2]);
		if (res != 0)
			return (res);
	}
	if ((!is_heredoc(av[1]) && i == 2) || (is_heredoc(av[1]) && i == 3))
	{
		infile = open(av[1], O_RDONLY);
		if (infile < 0)
			return (perror("failed to open infile"),
				close(fd[1]), ft_dup2(fd[0], 0), -2);
		ft_dup2(infile, 0);
	}
	return (0);
}
