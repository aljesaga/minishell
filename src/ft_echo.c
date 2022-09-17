/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:29:04 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/17 18:44:35 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	echo
	Write arguments to the standard output.
		- With option -n (Do not append a newline)
*/

int	ft_echo(t_comand *com)
{
	int	i;

	i = 1;
	while (com->comand[i])
	{
		ft_putstr_fd(com->comand[i], com->fd_out);
		ft_putchar_fd(' ', com->fd_out);
		i++;
	}
	ft_putchar_fd('\n', com->fd_out);
	return (0);
}
