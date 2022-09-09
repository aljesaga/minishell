/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:20:55 by ioriola           #+#    #+#             */
/*   Updated: 2022/09/09 17:07:54 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	pwd
	Print the name of the current working directory.
		- With no options
*/

int	ft_pwd(t_comand *com)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, com->fd_out);
		ft_putchar_fd('\n', com->fd_out);
		free(cwd);
		return (0);
	}
	return (1);
}
