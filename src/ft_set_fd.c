/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:48:26 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/11 17:06:15 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_take_msn(char *std, t_mshell *mini, int check)
{
	char	*temp;
	char	*aux;
	size_t	len;

	len = ft_strlen(std);
	close(mini->fd_out);
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
		if (check == 0)
		{
			aux = temp;
			temp = str_expand(aux, mini);
			free(aux);
		}
		printf("---->%s", temp);
		ft_putstr_fd(temp, mini->fd_in);
		free(temp);
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
