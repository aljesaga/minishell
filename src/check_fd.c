/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:50:42 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/09 12:29:26 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_take_msn(char *std, t_mshell *mini)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(std);
	close (mini->fd_out);
	while (1)
	{
		ft_putstr_fd("IA_minishell->heredoc: ", 1);
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
		ft_putstr_fd(temp, mini->fd_in);
		free(temp);
	}
}

static int	ft_here_doc(t_mshell *mini, char *arv)
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
		return (here[FD_R]);
	}
}

void	build_tunnel(t_mshell *mini, t_comand *new)
{
	int	fd[2];

	pipe(fd);
	mini->fd_in = fd[FD_R];
	new->fd_out = fd[FD_W];
}

void	check_fd(t_mshell *mini, t_comand *new, t_section *now)
{
	char	*temp;

	if (now->type == 1)
	{
		if (now->next->str[0] != '/')
			temp = ft_strjoin("./", now->next->str);
		if (access(temp, F_OK))
		{
			printf("%s: no encontrado\n", now->next->str);
			free(temp);
		}
		new->fd_in = open(now->next->str, O_RDONLY, 0644);
		if (new->fd_in < 0)
			new->fd_in = STDIN_FILENO;
	}
	else if (now->type == 2)
		new->fd_in = ft_here_doc(mini, now->next->str);
	else if (now->type == 3)
		new->fd_out = open(now->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (now->type == 4)
		new->fd_out = open(now->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
}
