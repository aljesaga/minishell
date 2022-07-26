/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:04:13 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/24 16:06:19 by alsanche         ###   ########lyon.fr   */
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

static void	change_pwd(char *aux, t_mshell *mini)
{
	char	**temp_pwd;

	temp_pwd = ft_calloc(sizeof(char *), 3);
	temp_pwd[0] = ft_strjoin("OLDPWD=", aux);
	free(aux);
	aux = getcwd(NULL, 0);
	temp_pwd[1] = ft_strjoin("PWD=", aux);
	free(aux);
	ft_export(temp_pwd, mini);
	free_split(temp_pwd);
}

int	ft_cd(char *line, t_mshell *mini)
{
	char	*aux;
	int		chdir_;

	if (!line || line[0] == '\0' || !ft_strcmp(line, "~\0"))
	{
		aux = get_env_value("HOME", mini);
		chdir_ = chdir(aux);
	}
	else
	{
		aux = get_env_value("PWD", mini);
		chdir_ = chdir(line);
	}
	if (chdir_ == -1)
	{
		free(aux);
		print_error(line);
		return (1);
	}
	change_pwd(aux, mini);
	return (0);
}
