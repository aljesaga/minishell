/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:48:26 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/17 18:06:03 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	build_tunnel(t_mshell *mini)
{
	int	fd[2];

	pipe(fd);
	mini->fd_in = fd[FD_R];
	return (fd[FD_W]);
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
		new->fd_in = open(now->next->str, O_RDONLY, 0644);
		if (new->fd_in < 0)
			new->fd_in = STDIN_FILENO;
	}
	else if (now->type == 2)
		new->fd_in = ft_here_doc(mini, now->next->str, now->next->here_expand);
	else if (now->type == 3)
		new->fd_out = open(now->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (now->type == 4)
		new->fd_out = open(now->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (now->type == 5)
		new->fd_out = build_tunnel(mini);
}

void	not_comand(t_mshell *mini, t_section *now)
{
	char	*temp;
	int		aux;

	aux = 0;
	if (now->type == 1)
	{
		if (now->next->str[0] != '/')
			temp = ft_strjoin("./", now->next->str);
		if (access(temp, F_OK))
		{
			printf("%s: No such file or directory\n", now->next->str);
			free(temp);
		}
		aux = open(now->next->str, O_RDONLY, 0644);
		if (aux < 0)
			aux = STDIN_FILENO;
	}
	else if (now->type == 2)
		aux = ft_here_doc(mini, now->next->str, now->next->here_expand);
	else if (now->type == 3)
		aux = open(now->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (now->type == 4)
		aux = open(now->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (aux > 0)
		close(aux);
}
