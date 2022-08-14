/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/14 15:50:04 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	analyze_line(char *line, t_mshell *mini)
{
	char	**args;

	if (!line)
		return (0);
	args = ft_split(line, ' ');
	mini->fd_out = STDOUT_FILENO;
	if (is_builtin(args[0]))
		run_builtin(args, line, mini);
	/*else
		run_binary(); << Todavía no existe. */
	free_split(args);
	return (0);
}
