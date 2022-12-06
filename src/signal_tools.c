/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:04:01 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/06 09:06:51 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_interrupt(int sig)
{
	signal(SIGINT, SIG_IGN);
	printf("Signal Interrupt\n");
	signal(SIGINT, &signal_interrupt);
}

void	signal_quit(int sig)
{
	signal(SIGQUIT, SIG_IGN);
	printf("Signal Quit\n");
	signal(SIGQUIT, &signal_quit);
}

int	signal_initialize(void)
{
	if (signal(SIGINT, &signal_interrupt) == SIG_ERR)
		return (0);
	if (signal(SIGQUIT, &signal_quit) == SIG_ERR)
		return (0);
	return (1);
}