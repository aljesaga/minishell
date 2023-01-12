/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:06:28 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/12 17:20:24 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_put(char *temp, int check, int here)
{
	char	*aux;

	if (check == 0)
	{
		aux = temp;
		temp = str_expand(aux);
		free(aux);
	}
	ft_putstr_fd(temp, here);
	ft_putchar_fd('\n', here);
	free(temp);
}

static int	ft_here_doc(char *arv, char *file, int check)
{	
	int		fd;
	char	*temp;

	fd = open(file, O_RDWR | O_APPEND);
	temp = readline("-> ");
	if (!temp || fd < 0)
		return (1);
	if (!ft_strncmp(temp, arv, ft_strlen(temp)))
	{
		free(temp);
		return (1);
	}
	check_put(temp, check, fd);
	close(fd);
	return (0);
}

void	exec_h_doc(t_section *arv, char *str, int check)
{
	signal(SIGINT, sig_redir);
	while (1)
	{
		if (ft_here_doc(arv->next->str, str, check) == 1)
			break ;
	}
	exit (0);
}

int	here_doc(t_section *arv, int check)
{
	char	*str;
	char	*aux;
	pid_t	h_doc;
	int		fd;

	aux = ft_itoa(arv->num);
	str = ft_strjoin("/tmp/.temp", aux);
	free(aux);
	h_doc = fork();
	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (h_doc > 0)
		g_mini->state = h_doc;
	else if (h_doc < 0)
		send_error(2, "fork");
	else
		exec_h_doc(arv, str, check);
	waitpid(h_doc, &g_mini->a_error, 0);
	if (WIFEXITED(g_mini->a_error))
		g_mini->l_exit = WEXITSTATUS(g_mini->a_error);
	unlink(str);
	free(str);
	return (fd);
}

static void	mini_type_3_4(t_section *now)
{
	char	*temp;

	if (now->type == 3 || now->type == 4)
	{
		if (now->next->str[0] != '/')
			temp = ft_strjoin("./", now->next->str);
		if (g_mini->fd_out != STDOUT_FILENO)
			close(g_mini->fd_out);
		if (now->type == 3)
			g_mini->fd_out = open(now->next->str, O_RDWR | O_CREAT
					| O_TRUNC, 0644);
		else if (now->type == 4)
			g_mini->fd_out = open(now->next->str, O_RDWR | O_CREAT
					| O_APPEND, 0644);
		if (access(temp, F_OK))
		{
			printf("minishell: %s: Permission denied\n", now->next->str);
			free(temp);
		}
	}
}

void	mini_check_fd(t_section *now)
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
		if (g_mini->fd_in != STDIN_FILENO)
			close(g_mini->fd_in);
		g_mini->fd_in = open(now->next->str, O_RDONLY, 0644);
		if (g_mini->fd_in < 0)
			g_mini->fd_in = 0;
	}
	else if (now->type == 2)
	{
		if (g_mini->fd_in != STDIN_FILENO)
			close(g_mini->fd_in);
		g_mini->fd_in = here_doc(now, now->next->here_expand);
	}
	else
		mini_type_3_4(now);
}
