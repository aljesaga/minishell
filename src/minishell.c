/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:50:39 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/28 13:32:56 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int arc, char **arv, char **env)
{
	char		*line;

	g_mini = malloc(sizeof(t_mshell));
	if (arc == 1 && arv && g_mini)
	{
		init_mini(env);
		while (1)
		{
			signal_initialize();
			ft_reset_main_fd();
			line = readline(LPURPLE "IA_minishell\% " RESET);
			if (line && *line)
			{
				add_history(line);
				g_mini->l_exit = analyze_line(line);
			}
			else if (line == NULL)
			{
				write(STDOUT_FILENO, "exit\n", 5);
				exit(0);
			}
			free(line);
		}
	}
	return (0);
}
