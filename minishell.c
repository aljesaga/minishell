/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:50:39 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/25 13:36:01 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*init_mini(char **env)
{
	t_mshell	*mini;

	mini = malloc(sizeof(t_mshell));
	if (!mini)
		exit (127);
	mini->fd_out = STDOUT_FILENO;
	mini->l_exit = 0;
	env_collec(env, mini);
	shlvlup(mini);
	return (mini);
}

int	main(int arc, char **arv, char **env)
{
	char		*line;
	t_mshell	*mini;

	if (arc == 1)
	{
		mini = init_mini(env);
		while (1)
		{
			line = readline(MAGENTA "IA_minishell > " RESET_C);
			analyze_line(line, mini);
			free(line);
			system("leaks minishell");
		}
	}
	else if (arv)
		write(1, "Not Need arv", 13);
	return (0);
}
