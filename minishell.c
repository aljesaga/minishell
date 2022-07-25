/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:50:39 by alsanche          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/24 13:44:01 by alsanche         ###   ########lyon.fr   */
=======
/*   Updated: 2022/07/23 10:32:33 by ioriola          ###   ########.fr       */
>>>>>>> 0d8a12dd9f5614f49175d4a199478bac45d38cb1
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
<<<<<<< HEAD
			line = readline(MAGENTA "IA_minishell > " RESET_C);
			analyze_line(line, mini);
=======
			mini = init_mini(env);
			line = readline(MAGENTA "IA_minishell " RESET);
			if (!ft_strncmp(line, "echo", 5))
				ft_echo(line, mini);
			if (!ft_strncmp(line, "exit\0", 5))
				exit (0);
			if (!ft_strncmp(line, "env\0", 4))
				print_env(mini);
			if (line[0] == 'c' && line[1] == 'd')
				ft_cd(line);
>>>>>>> 0d8a12dd9f5614f49175d4a199478bac45d38cb1
			free(line);
		}
	}
	else if (arv)
		write(1, "Not Need arv", 13);
	return (0);
}
