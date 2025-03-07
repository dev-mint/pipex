/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:44:43 by anachat           #+#    #+#             */
/*   Updated: 2025/03/07 12:55:14 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PIPEX_H
# define BONUS_PIPEX_H

# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include <stdio.h>
# include <fcntl.h>

char	*get_path(char *cmd, char **env);
void	free_arr(char **arr);
int		ft_dup2(int oldfd, int newfd);
void	ft_close2(int fd1, int fd2);

int		file_check(char **av, int i);
int		is_heredoc(char *arg);

#endif
