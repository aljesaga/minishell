/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:29:04 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/16 19:26:33 by alsanche         ###   ########lyon.fr   */
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
	int	check;

	if (!com->comand[1])
		ft_putchar_fd('\n', com->fd_out);
	else
	{
		if (!ft_strncmp(com->comand[1], "-n\0", 3))
			i = 2;
		else
			i = 1;
		check = i;
		while (check == 2 && !ft_strncmp(com->comand[i], "-n\0", 3))
			i++;
		while (com->comand[i])
		{
			ft_putstr_fd(com->comand[i], com->fd_out);
			if (com->comand[i + 1])
				ft_putchar_fd(' ', com->fd_out);
			i++;
		}
		if (check == 1)
			ft_putchar_fd('\n', com->fd_out);
	}
	return (0);
}
