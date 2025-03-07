/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:18:31 by anachat           #+#    #+#             */
/*   Updated: 2025/03/07 15:51:30 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	write_input(char *end)
{
	char	*line;
	int		len;
	int		fd;

	fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
		return (perror("cannot open heredoc file"), -1);
	line = get_next_line(0);
	if (!line)
		return (perror("cannot read from stdin"), close(fd), -1);
	while (line)
	{
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
			break ;
		line[len - 1] = '\n';
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	return (close(fd), free(line), 0);
}

int file_check(char **av, int i)
{
	int	infile;

	if (is_heredoc(av[1]) && i == 3)
		return (write_input(av[2]));
	if ((!is_heredoc(av[1]) && i == 2) || (is_heredoc(av[1]) && i == 3))
	{
		infile = open(av[1], O_RDONLY);
		if (infile < 0)
			return (perror("failed to open infile"), -1);
		ft_dup2(infile, 0);
	}
	return (0);
}
