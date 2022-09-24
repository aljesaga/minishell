/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:48:26 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/24 19:51:29 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*build_tunnel(t_comand *com, t_comand *aux)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	pipe(fd);
	aux->fd_in = fd[FD_R];
	if (com->fd_out == 1)
		com->fd_out = fd[FD_W];
	return (fd);
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
		new->pipe = 1;
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
