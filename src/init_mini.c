/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:03:58 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/28 13:32:35 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_name(void)
{
	printf(CYAN "███████████████████████████████████████████████████████\n");
	printf(LCYAN "█  █████  ████████████████████████  ████████████  ██  █\n");
	printf(CYAN "█   ███   ██  ██  █████  ███   ███  ██████   ███  ██  █\n");
	printf(LCYAN "█    █    ██████     ██████  █  ██    ███  █  ██  ██  █\n");
	printf(CYAN"█  █   █  ██  ██  █  ██  ███  ████  █  ██     ██  ██  █\n");
	printf(LCYAN "█  ██ ██  ██  ██  █  ██  ████  ███  █  ██  █████  ██  █\n");
	printf(CYAN "█  █████  ██  ██  █  ██  ██  █  ██  █  ██  █  ██  ██  █\n");
	printf(LCYAN "█  █████  ██  ██  █  ██  ███   ███  █  ███   ███  ██  █\n");
	printf(CYAN "███████████████████████████████████████████████████████\n");
}

void	init_mini(char **env)
{
	g_mini->fd_out = STDOUT_FILENO;
	g_mini->l_exit = 0;
	g_mini->state = 0;
	g_mini->n_env = 0;
	if (!env || env[0] == NULL)
	{
		env = ft_split("PWD=/Users/alsanche/minishell:SHLVL=1:OLDPWD", ':');
		env_collec(env);
		free(env);
	}
	else
		env_collec(env);
	unset_mini();
	shlvlup();
	print_name();
}
