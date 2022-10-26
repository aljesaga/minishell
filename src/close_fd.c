/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:49 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/26 18:56:51 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_reset_main_fd(t_mshell *mini)
{
	if (mini->fd_in != STDIN_FILENO)
		close(mini->fd_in);
	mini->fd_in = STDIN_FILENO;
	if (mini->fd_out != STDOUT_FILENO)
		close(mini->fd_out);
	mini->fd_out = STDOUT_FILENO;
}

void	ft_close_fd(int fd_in, t_mshell *mini)
{
	int	i;

	i = -1;
	while (++i < mini->n_com - 1)
	{
		if (mini->pipex[i][0] != 0 && mini->pipex[i][0] != fd_in)
			close(mini->pipex[i][0]);
		if (mini->pipex[i][1] != 1)
			close(mini->pipex[i][1]);
	}
}

void	ft_free_fd(t_mshell *mini)
{
	int	i;

	i = -1;
	while (++i < mini->n_com - 1)
	{
		if (mini->pipex[i])
			free(mini->pipex[i]);
	}
	free(mini->pipex);
}
