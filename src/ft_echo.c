/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:29:04 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/30 16:29:46 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	echo
	Write arguments to the standard output.
		- With option -n (Do not append a newline)
*/

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
