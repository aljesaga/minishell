/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:29:04 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/24 13:34:54 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **str, t_mshell *mini)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i][0] == '$' && str[i][1] == '?')
		{
			ft_putnbr_fd(mini->l_exit, mini->fd_out);
			ft_putchar_fd('\n', mini->fd_out);
			return (0);
		}
		ft_putstr_fd(str[i], mini->fd_out);
		ft_putchar_fd(' ', mini->fd_out);
		i++;
	}
	return (0);
}
