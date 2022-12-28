/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:49 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/28 13:43:20 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_reset_main_fd(void)
{
	if (g_mini->fd_in != STDIN_FILENO)
		close(g_mini->fd_in);
	g_mini->fd_in = STDIN_FILENO;
	if (g_mini->fd_out != STDOUT_FILENO)
		close(g_mini->fd_out);
	g_mini->fd_out = STDOUT_FILENO;
}

void	ft_close_fd(int fd_in)
{
	int	i;

	i = -1;
	while (++i < g_mini->n_com - 1)
	{
		if (g_mini->pipex[i][0] != 0 && g_mini->pipex[i][0] != fd_in)
			close(g_mini->pipex[i][0]);
		if (g_mini->pipex[i][1] != 1)
			close(g_mini->pipex[i][1]);
	}
}

void	ft_free_fd(void)
{
	int	i;

	i = -1;
	while (++i < g_mini->n_com - 1)
	{
		if (g_mini->pipex[i])
			free(g_mini->pipex[i]);
	}
	free(g_mini->pipex);
}
