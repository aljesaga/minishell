/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:04:01 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/21 10:18:08 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_interrupt(int sig)
{
	signal(SIGINT, SIG_IGN);
	printf("Signal Interrupt (%i)\n", sig);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//l_exit = 1
	signal(SIGINT, &signal_interrupt);
}

void	signal_quit(int sig)
{
	signal(SIGQUIT, SIG_IGN);
	printf("Signal Quit (%i)\n", sig);
	rl_on_new_line();
	rl_replace_line(rl_line_buffer, rl_end);
	rl_redisplay();
	signal(SIGQUIT, &signal_quit);
}

int	signal_initialize(void)
{
	if (signal(SIGINT, &signal_interrupt) == SIG_ERR)
	{
		//EXIT PROGRAM??
		return (0);
	}
	if (signal(SIGQUIT, &signal_quit) == SIG_ERR)
	{
		//EXIT PROGRAM??
		return (0);
	}
	return (1);
}