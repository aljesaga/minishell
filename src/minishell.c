/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:50:39 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/14 14:12:25 by alsanche         ###   ########lyon.fr   */
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
			line = readline(LIGHTPURPLE "IA_minishell\% " RESET);
			analyze_line(line, mini);
			free(line);
			system("leaks -list -quiet minishell");
		}
	}
	else if (arv)
		write(1, "Not Need arv", 13);
	return (0);
}
