/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:57:22 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/18 16:14:18 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_exit(char *str, int fd_out)
{
	int		num;
	char	*nume;

	num = ft_atoi(str);
	nume = ft_itoa(num);
	if (strncmp(str, nume, ft_strlen(str)) != 0)
	{
		free(nume);
		ft_putstr_fd("IA_minishell: exit: ", fd_out);
		ft_putstr_fd(str, fd_out);
		ft_putstr_fd(": numeric argument required\n", fd_out);
		return (255);
	}
	free(nume);
	return (0);
}

void	ft_exit(t_comand *com)
{
	int	ex;

	ex = g_mini->l_exit;
	if (g_mini->n_com <= 1)
		ft_putstr_fd("exit\n", com->fd_out);
	if (com->n_arg <= 2)
	{
		if (com->n_arg == 2)
		{
			if (check_exit(com->comand[1], com->fd_out) == 255)
				ex = 255;
			else
			{
				ex = ft_atoi(com->comand[1]);
				ex = ex % 256;
			}
		}
		exit (ex);
	}
	else
		ft_putstr_fd("IA_minishell: exit: too many arguments\n", com->fd_out);
}
