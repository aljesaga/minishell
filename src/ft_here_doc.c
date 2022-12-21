/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:06:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/21 15:52:22 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_put(char *temp, t_mshell *mini, int check, int here)
{
	char	*aux;

	if (check == 0)
	{
		aux = temp;
		temp = str_expand(aux, mini);
		free(aux);
	}
	ft_putstr_fd(temp, here);
	ft_putchar_fd('\n', here);
	free(temp);
}

static int	ft_here_doc(t_mshell *mini, char *arv, char *file, int check)
{	
	int		fd;
	size_t	len;
	char	*temp;

	fd = open(file, O_RDWR | O_APPEND);
	len = ft_strlen(arv);
	temp = readline("-> ");
	if (!temp || fd < 0)
		return (1);
	if (!ft_strncmp(temp, arv, len))
	{
		free(temp);
		return (1);
	}
	check_put(temp, mini, check, fd);
	close(fd);
	return (0);
}

int	here_doc(t_mshell *mini, t_section *arv, int check)
{
	char	*str;
	char	*aux;
	int		fd;
	pid_t	child;

	aux = ft_itoa(arv->num);
	str = ft_strjoin("/tmp/.temp", aux);
	free(aux);
	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	child = fork();
	if (child < 0)
		exit (1);
	if (child == 0)
	{
		signal_heredoc();
		while (1)
			if (ft_here_doc(mini, arv->next->str, str, check) == 1)
				break ;
		g_l_exit = 1;
		exit (1);
	}
	wait(&child);
	return (fd);
}

static void	mini_type_3_4(t_mshell *mini, t_section *now)
{
	char	*temp;

	if (now->type == 3 || now->type == 4)
	{
		if (now->next->str[0] != '/')
			temp = ft_strjoin("./", now->next->str);
		if (access(temp, F_OK))
		{
			printf("minishell: %s: Permission denied\n", now->next->str);
			free(temp);
		}
		else
		{
			if (mini->fd_out != STDOUT_FILENO)
				close(mini->fd_out);
			if (now->type == 3)
				mini->fd_out = open(now->next->str, O_RDWR | O_CREAT
						| O_TRUNC, 0644);
			else if (now->type == 4)
				mini->fd_out = open(now->next->str, O_RDWR | O_CREAT
						| O_APPEND, 0644);
		}
	}
}

void	mini_check_fd(t_mshell *mini, t_section *now)
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
		if (mini->fd_in != STDIN_FILENO)
			close(mini->fd_in);
		mini->fd_in = open(now->next->str, O_RDONLY, 0644);
		if (mini->fd_in < 0)
			mini->fd_in = STDIN_FILENO;
	}
	else if (now->type == 2)
	{
		if (mini->fd_in != STDIN_FILENO)
			close(mini->fd_in);
		mini->fd_in = here_doc(mini, now, now->next->here_expand);
	}
	else
		mini_type_3_4(mini, now);
}
