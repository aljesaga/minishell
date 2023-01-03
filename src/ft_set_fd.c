/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:48:26 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/03 11:16:33 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	type_5_8(t_comand *new, t_section *now)
{	
	if (now->type == 5)
	{
		g_mini->fd_in = STDIN_FILENO;
		g_mini->fd_out = STDOUT_FILENO;
		new->pipe = 1;
	}
	else if (now->type == 8)
	{
		g_mini->fd_in = STDIN_FILENO;
		g_mini->fd_out = STDOUT_FILENO;
		new->wait = 1;
	}
}

static void	type_3_4(t_comand *new, t_section *now)
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
		type_5_8(new, now);
}

void	check_fd(t_comand *new, t_section *now)
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
		new->fd_in = here_doc(now, now->next->here_expand);
	}
	else
		type_3_4(new, now);
}
