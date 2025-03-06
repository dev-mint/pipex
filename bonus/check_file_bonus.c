/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:18:31 by anachat           #+#    #+#             */
/*   Updated: 2025/03/06 17:17:33 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int file_check(char **av, int i)
{
	int infile;

	if (i == 2)
	{

		infile = open(av[1], O_RDONLY);
		if (infile < 0)
			return (perror("failed to open infile"), -1);
		dup2(infile, 0);
	}
	return (0);
}

// int	check_file(int ac, char **av, int *fd)
// {
// 	int	is_herdoc;
// 	int infile;
	
// 	if (ft_strncmp(av[1], "here_doc", 9) == 0)
// 		is_herdoc = 1;
// 	else
// 		is_herdoc = 0;
// 	if (is_herdoc)
// 	{
// 		if (ac < 6)
// 			return (perror("here_doc cmd needs to be passed 6 args"), 0);
// 		//
// 	}
// 	else
// 	{
// 		infile = open(av[1], O_RDONLY);
// 		if (infile < 0)
// 			return (perror("failed to open infile"), close(fd[1]), 1);
// 	}
// }