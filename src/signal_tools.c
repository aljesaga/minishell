/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:04:01 by ioriola           #+#    #+#             */
/*   Updated: 2023/01/12 16:21:24 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT && g_mini->state == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_mini->l_exit = 1;
	}
	else if (sig == SIGQUIT && g_mini->state == 0)
	{
		printf("exit");
		rl_on_new_line();
		rl_replace_line(rl_line_buffer, rl_end);
		rl_redisplay();
		exit(1);
	}
	if (g_mini->state > 0)
		kill(g_mini->state, SIGCONT);
}

void	sig_redir(int sig)
{
	if (sig == SIGINT)
		exit (0);
}

int	signal_initialize(void)
{
	if (g_mini->state == 0)
	{
		if (signal(SIGINT, &signal_handler) == SIG_ERR)
			return (0);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		return (1);
	}
	return (1);
}
