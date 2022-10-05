/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:49 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/05 14:39:02 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_close_fd(int fd_in, t_mshell *mini)
{
	int	i;

	i = -1;
	while (++i < mini->n_com - 1)
	{
		if (mini->pipex[i] != 0 && mini->pipex[i] != fd_in)
			close(mini->pipex[i]);
		if (mini->pipex[i] != 1)
			close(mini->pipex[i]);
	}
}
