/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:03:58 by ioriola           #+#    #+#             */
/*   Updated: 2023/01/19 17:15:27 by alsanche         ###   ########lyon.fr   */
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
		free_split(env);
	}
	else
		env_collec(env);
	unset_mini();
	shlvlup();
	print_name();
}
