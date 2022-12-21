/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:04:01 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/21 10:55:09 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//g_l_exit = 1
		signal(SIGINT, &signal_handler);
	}
	else if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		rl_on_new_line();
		rl_replace_line(rl_line_buffer, rl_end);
		rl_redisplay();
		signal(SIGQUIT, &signal_handler);
	}
}

int	signal_initialize(void)
{
	if (signal(SIGINT, &signal_handler) == SIG_ERR)
	{
		//EXIT PROGRAM??
		return (0);
	}
	return (1);
}