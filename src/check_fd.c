/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:50:42 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/10 17:16:45 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_here_doc(t_mshell *mini, char *arv)
{	
	int		here[2];
	pid_t	child;

	pipe(here);
	child = fork();
	if (child < 0 || here[FD_R] < 0)
		ft_putstr_fd("here_doc failed", 1);
	mini->fd_in = here[FD_W];
	mini->fd_out = here[FD_R];
	if (child == 0)
	{
		ft_take_msn(arv, mini);
	}
	else
	{
		waitpid(child, NULL, 0);
		close(here[FD_W]);
		mini->fd_in = here[FD_R];
	}
}

void	check_fd(t_mshell *mini, char **arv, int i)
{
	char	*temp;

	if (!ft_strncmp(arv[i], "<\0", 2))
	{
		if (arv[i][0] != '/')
			temp = ft_strjoin("./", arv[1]);
		if (access(temp, F_OK))
		{
			send_error(3, arv[i]);
			free(temp);
		}
		mini->fd_in = open(arv[1], O_RDONLY, 0644);
		if (mini->fd_in < 0)
			mini->fd_in = STDIN_FILENO;
	}
	else if (!ft_strncmp(arv[i], "<<\0", 3))
		ft_here_doc(mini, arv[i + 1]);
	else if (!ft_strncmp(arv[i], ">\0", 2))
		mini->fd_out = open(mini->file_out, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strncmp(arv[i], ">>\0", 3))
		mini->fd_out = open(mini->file_out, O_RDWR | O_CREAT | O_APPEND, 0644);
}
