/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:50:39 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/21 12:14:14 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int arc, char **arv, char **env)
{
	char		*line;
	t_mshell	*mini;

	if (arc == 1 && arv)
	{
		mini = init_mini(env);
		while (1)
		{
			ft_reset_main_fd(mini);
			signal_initialize();
			line = readline(LPURPLE "IA_minishell\% " RESET);
			if (line && *line)
			{
				add_history(line);
				g_l_exit = analyze_line(line, mini);
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
