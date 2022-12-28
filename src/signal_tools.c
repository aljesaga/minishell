/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:04:01 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/28 13:36:17 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_mini->l_exit = 1;
	}
	else if (sig == SIGQUIT)
	{
		printf("exit");
		rl_on_new_line();
		rl_replace_line(rl_line_buffer, rl_end);
		rl_redisplay();
		exit(1);
	}
}

void	sig_redir(int sig)
{
	if (sig == SIGINT)
	{
		g_mini->l_exit = 0;
		exit (0);
	}
}

void	signal_child(void)
{
	signal(SIGINT, sig_redir);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_heredoc(int sig)
{
	g_mini->state = 0;
	(void)sig;
	printf("estoy aqui %d\n", g_mini->state);
	rl_on_new_line();
	rl_line_buffer[0] = '\0';
	rl_point = 0;
	rl_end = 0;
	rl_redisplay();
	g_mini->l_exit = 1;
}

int	signal_initialize(void)
{
	if (g_mini->state == 2)
		signal(SIGINT, &signal_heredoc);
	else if (signal(SIGINT, &signal_handler) == SIG_ERR)
		return (0);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
