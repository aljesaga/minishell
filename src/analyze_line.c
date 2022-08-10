/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/10 16:53:47 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	n_comand(t_mshell *mini, char **arv)
{
	int	i;

	i = -1;
	mini->n_com = 1;
	while (arv[++i])
	{
		if (arv[i][0] == '<')
			check_fd(mini, arv, i);
		if (arv[i][0] == '|')
			mini->n_com++;
	}
}

int	analyze_line(char *line, t_mshell *mini)
{
	char	**args;

	if (!line)
		return (0);
	args = ft_split(line, ' ');
	mini->fd_out = STDOUT_FILENO;
	if (is_builtin(args[0]))
		run_builtin(args, line, mini);
	else
	//	run_binary(); << Todavía no existe. 
	free_split(args);
	return (0);
}
