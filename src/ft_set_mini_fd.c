/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_mini_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:26:01 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/26 17:16:21 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

/*static void	mini_type_3_4(t_mshell *mini, t_section *now)
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
}*/
