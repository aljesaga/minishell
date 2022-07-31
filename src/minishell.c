/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:50:39 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/31 17:54:47 by ioriola          ###   ########.fr       */
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
			printf("-----------\n");
			line = readline(LIGHTPURPLE "IA_minishell > " RESET);
			analyze_line(line, mini);
			free(line);
			system("leaks -list -quiet minishell");
		}
	}
	else if (arv)
		write(1, "Not Need arv", 13);
	return (0);
}
