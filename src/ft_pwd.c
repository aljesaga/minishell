/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:20:55 by ioriola           #+#    #+#             */
/*   Updated: 2022/07/31 10:55:55 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	pwd
	Print the name of the current working directory.
		- With no options
*/

int	ft_pwd(t_mshell *mini)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, mini->fd_out);
		ft_putchar_fd('\n', mini->fd_out);
		free(cwd);
		return (0);
	}
	return (1);
}
