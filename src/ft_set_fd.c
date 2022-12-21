/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:48:26 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/21 15:49:52 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*build_tunnel(t_comand *com, t_mshell *mini)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	pipe(fd);
	ft_reset_main_fd(mini);
	mini->fd_in = fd[FD_R];
	if (com->fd_out == STDOUT_FILENO)
		com->fd_out = fd[FD_W];
	return (fd);
}

static void	type_5_8(t_mshell *mini, t_comand *new, t_section *now)
{	
	if (now->type == 5)
		mini->pipex[new->n_comand] = build_tunnel(new, mini);
	else if (now->type == 8)
	{
		ft_reset_main_fd(mini);
		new->wait = 1;
	}
}

static void	type_3_4(t_mshell *mini, t_comand *new, t_section *now)
{
	char	*temp;

	if (now->type == 3 || now->type == 4)
	{
		if (new->fd_out != STDOUT_FILENO)
			close(new->fd_out);
		if (now->type == 3)
			new->fd_out = open(now->next->str, O_RDWR | O_CREAT
					| O_TRUNC, 0644);
		else if (now->type == 4)
			new->fd_out = open(now->next->str, O_RDWR | O_CREAT
					| O_APPEND, 0644);
		if (now->next->str[0] != '/')
			temp = ft_strjoin("./", now->next->str);
		if (access(temp, F_OK))
		{
			printf("minishell: %s: Permission denied\n", now->next->str);
			free(temp);
		}
	}
	else
		type_5_8(mini, new, now);
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
			printf("%s: No such file or directory\n", now->next->str);
			free(temp);
		}
		if (new->fd_in != STDIN_FILENO)
			close(new->fd_in);
		new->fd_in = open(now->next->str, O_RDONLY, 0644);
		if (new->fd_in < 0)
			new->fd_in = STDIN_FILENO;
	}
	else if (now->type == 2)
	{
		if (new->fd_in != STDIN_FILENO)
			close(new->fd_in);
		new->fd_in = here_doc(mini, now, now->next->here_expand);
	}
	else
		type_3_4(mini, new, now);
}
