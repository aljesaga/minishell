/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:06:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/11/26 19:17:21 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_put(char *temp, t_mshell *mini, int check, int *here)
{
	char	*aux;

	if (check == 0)
	{
		aux = temp;
		temp = str_expand(aux, mini);
		free(aux);
	}
	ft_putstr_fd(temp, here[FD_W]);
	ft_putchar_fd('\n', here[FD_W]);
	free(temp);
}

int	ft_here_doc(t_mshell *mini, char *arv, int check)
{	
	int		here[2];
	size_t	len;
	char	*temp;

	pipe(here);
	len = ft_strlen(arv);
	while (1)
	{
		temp = readline("-> ");
		if (!temp)
			break ;
		if (!ft_strncmp(temp, arv, len))
		{
			free(temp);
			break ;
		}
		check_put(temp, mini, check, here);
	}
	close(here[FD_W]);
	return (here[FD_R]);
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
		mini->fd_in = ft_here_doc(mini, now->next->str, now->next->here_expand);
	}
	else
		mini_type_3_4(mini, now);
}
