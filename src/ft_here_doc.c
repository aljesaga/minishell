/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:06:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/18 12:31:56 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_put(char *temp, t_mshell *mini, int check)
{
	char	*aux;

	if (check == 0)
	{
		aux = temp;
		temp = str_expand(aux, mini);
		free(aux);
	}
	ft_putstr_fd(temp, mini->fd_in);
	free(temp);
}

static void	ft_take_msn(char *std, t_mshell *mini, int check)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(std);
	close(mini->fd_out);
	while (1)
	{
		ft_putstr_fd("IA_minishell-> ", 1);
		temp = get_next_line(STDIN_FILENO);
		if (!temp)
		{
			close (mini->fd_in);
			exit (1);
		}
		if (!ft_strncmp(temp, std, len) && temp[len] == '\n')
		{
			close (mini->fd_in);
			free(temp);
			exit (0);
		}
		check_put(temp, mini, check);
	}
}

int	ft_here_doc(t_mshell *mini, char *arv, int check)
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
		ft_take_msn(arv, mini, check);
	}
	else
	{
		waitpid(child, NULL, 0);
		close(here[FD_W]);
	}
	return (here[FD_R]);
}
