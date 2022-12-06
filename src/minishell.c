/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:50:39 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/06 09:05:37 by ioriola          ###   ########.fr       */
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
			ft_reset_main_fd(mini);
			if (signal_initialize())
				printf("Signal Initialized\n");
			line = readline(LPURPLE "IA_minishell\% " RESET);
			add_history(line);
			mini->l_exit = analyze_line(line, mini);
			free(line);
			// system("leaks -list -quiet minishell");
		}
	}
	else if (arv)
		write(1, "Not Need arv", 13);
	return (0);
}
