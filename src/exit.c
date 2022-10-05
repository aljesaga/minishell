/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:57:22 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/05 17:39:37 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(t_comand *com, t_mshell *mini)
{
	ft_putstr_fd("exit\n", 2);
	if (com->n_arg >= 2)
	{
		if ()
	}
	else
		ft_putstr_fd("IA_minishell: exit: too many arguments\n", 2);
}
