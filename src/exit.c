/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:57:22 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/12 17:29:43 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_exit(char *str)
{
	int		num;
	char	*nume;

	num = ft_atoi(str);
	nume = ft_itoa(num);
	if (strncmp(str, nume, ft_strlen(str)) != 0)
	{
		free(nume);
		return (255);
	}
	free(nume);
	return (0);
}

void	ft_exit(t_comand *com, t_mshell *mini)
{
	int	ex;

	ex = mini->l_exit;
	ft_putstr_fd("exit\n", 2);
	if (com->n_arg <= 2)
	{
		if (com->n_arg == 2)
		{
			if (check_exit(com->comand[1]) == 255)
			{
				ft_putstr_fd("IA_minishell: exit: ", 2);
				ft_putstr_fd(com->comand[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				ex = 255;
			}
			else
			{
				ex = ft_atoi(com->comand[1]);
				ex = ex % 256;
			}
		}
		exit (ex);
	}
	else
		ft_putstr_fd("IA_minishell: exit: too many arguments\n", 2);
}
