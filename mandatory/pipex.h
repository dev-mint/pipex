/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:44:43 by anachat           #+#    #+#             */
/*   Updated: 2025/02/22 17:05:31 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

char	*get_path(char *cmd, char **env);
void	free_arr(char **arr);
int		ft_dup2(int oldfd, int newfd);

#endif
