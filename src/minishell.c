/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:50:39 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/22 16:23:05 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int arc, char **arv, char **env)
{
	char		*line;
	t_mshell	*mini;

	if (arc == 1)
	{
		mini = init_mini(env);
		while (1)
		{
			mini->fd_in = STDIN_FILENO;
			mini->fd_out = STDOUT_FILENO;
			line = readline(LIGHTPURPLE "IA_minishell\% " RESET);
			add_history(line);
			mini->l_exit = analyze_line(line, mini);
			free(line);
			system("leaks -list -quiet minishell");
		}
	}
	else if (arv)
		write(1, "Not Need arv", 13);
	return (0);
}
