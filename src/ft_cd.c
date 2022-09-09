/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:04:13 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/09 12:32:28 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	cd
	Change the shell working directory.
		- With only a relative or absolute path
*/

void	print_error(char *line)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(line, 2);
	ft_putchar_fd('\n', 2);
}

int	ft_cd(char *line, t_mshell *mini)
{
	char	*temp_pwd;
	char	*temp_line;
	int		chdir_;

	temp_line = line + 3;
	free (line);
	temp_line = ft_strtrim(temp_line, " ");
	temp_pwd = get_env_value("PWD", mini);
	chdir_ = chdir(temp_line);
	if (chdir_ == -1)
	{
		print_error(temp_line);
		return (1);
	}
	ft_export(ft_strjoin("OLDPWD=", temp_pwd), mini);
	ft_export(ft_strjoin("PWD=", getcwd(NULL, 0)), mini);
	return (0);
}
