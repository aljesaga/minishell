/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:04:01 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/23 13:50:56 by alsanche         ###   ########lyon.fr   */
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
		g_l_exit = 1;
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
		g_l_exit = 0;
		exit (0);
	}
}

void	signal_child(void)
{
	signal(SIGINT, sig_redir);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_heredoc(void)
{
	signal(SIGINT, sig_redir);
	signal(SIGQUIT, SIG_IGN);
}

int	signal_initialize(void)
{
	if (signal(SIGINT, &signal_handler) == SIG_ERR)
	{
		return (0);
	}
	return (1);
}
