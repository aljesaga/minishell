/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:04:13 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/18 14:50:15 by alsanche         ###   ########lyon.fr   */
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
	char	**temp_pwd;
	char	*temp_line;
	int		chdir_;

	temp_line = ft_strtrim(line, " ");
	temp_pwd = ft_calloc(sizeof(char *), 4);
	temp_pwd[0] = get_env_value("PWD", mini);
	chdir_ = chdir(temp_line);
	if (chdir_ == -1)
	{
		print_error(temp_line);
		return (1);
	}
	temp_pwd[1] = ft_strjoin("OLDPWD=", temp_pwd[0]);
	temp_pwd[2] = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_export(temp_pwd, mini);
	free_split(temp_pwd);
	return (0);
}
