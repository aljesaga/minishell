/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:49 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/29 13:58:13 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_reset_main_fd(void)
{
	if (g_mini->fd_in != 0)
		close(g_mini->fd_in);
	g_mini->fd_in = 0;
	if (g_mini->fd_out != 1)
		close(g_mini->fd_out);
	g_mini->fd_out = 1;
}

void	ft_asign_pipe(int *fd, t_comand *com)
{
	com->close = fd[0];
	if (com->fd_in == 0)
		com->fd_in = g_mini->fd_in;
	if (com->fd_out == 1)
		com->fd_out = fd[1];
	g_mini->fd_in = fd[0];
}
