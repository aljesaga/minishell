/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:29:04 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/25 15:51:16 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	echo
	Write arguments to the standard output.
		- With option -n (Do not append a newline)
*/

static int	check_n(char *str)
{
	int	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[++i] != '\0')
		{
			if (str[i] != 'n')
				return (1);
		}
		return (0);
	}
	return (1);
}

int	ft_echo(t_comand *com)
{
	int	i;
	int	check;

	if (!com->comand[1])
		ft_putchar_fd('\n', com->fd_out);
	else
	{
		if (check_n(com->comand[1]) == 0)
			i = 2;
		else
			i = 1;
		check = i;
		while (check == 2 && check_n(com->comand[i]) == 0)
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
