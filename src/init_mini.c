/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:03:58 by ioriola           #+#    #+#             */
/*   Updated: 2022/10/24 15:47:16 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_name(void)
{
	printf(WHITE "#######################################################\n");
	printf(PURPLE "#  #####  ########################  ############  ##  #\n");
	printf(BLUE "#   ###   ##  ##  #####  ###   ###  ######   ###  ##  #\n");
	printf(CYAN "#    #    ######     ######  #  ##    ###  #  ##  ##  #\n");
	printf(GREEN"#  #   #  ##  ##  #  ##  ###  ####  #  ##     ##  ##  #\n");
	printf(CYAN "#  ## ##  ##  ##  #  ##  ####  ###  #  ##  #####  ##  #\n");
	printf(BLUE "#  #####  ##  ##  #  ##  ##  #  ##  #  ##  #  ##  ##  #\n");
	printf(PURPLE "#  #####  ##  ##  #  ##  ###   ###  #  ###   ###  ##  #\n");
	printf(WHITE "#######################################################\n");
}

t_mshell	*init_mini(char **env)
{
	t_mshell	*mini;

	mini = malloc(sizeof(t_mshell));
	if (!mini)
		exit (127);
	mini->fd_out = STDOUT_FILENO;
	mini->l_exit = 0;
	mini->n_env = 0;
	if (!env || env[0] == NULL)
	{
		env = ft_split("PWD=/Users/alsanche/minishell:SHLVL=1:OLDPWD", ':');
		env_collec(env, mini);
		free(env);
	}
	else
		env_collec(env, mini);
	unset_mini(mini);
	shlvlup(mini);
	print_name();
	return (mini);
}
