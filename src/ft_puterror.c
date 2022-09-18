/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:03:35 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/18 17:51:30 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	send_error(int n, char *str)
{
	char	*temp;

	ft_putstr_fd("IA_minishell: ", 1);
	if (n == 0)
	{	
		temp = ft_strjoin(str, ": permission denied\n");
		ft_putstr_fd(temp, 1);
	}
	else if (n == 1)
	{
		temp = ft_strjoin(str, ": command not found\n");
		ft_putstr_fd(temp, 1);
	}
	else if (n == 2)
	{
		temp = ft_strjoin(str, ": it doesn't work\n");
		ft_putstr_fd(temp, 1);
	}
	else
	{
		temp = ft_strjoin(str, ": no such file or directory\n");
		ft_putstr_fd(temp, 1);
	}
	free(temp);
}

void	ft_puterror(char *funtion, char *str)
{
	ft_putstr_fd("IA_minishell: ", STDOUT_FILENO);
	ft_putstr_fd(funtion, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putchar_fd('`', STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
}
