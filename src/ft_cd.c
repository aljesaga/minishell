/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:04:13 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/12 14:48:19 by alsanche         ###   ########lyon.fr   */
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
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

static void	change_pwd(char *aux)
{
	char	**temp_pwd;

	temp_pwd = ft_calloc(sizeof(char *), 3);
	temp_pwd[0] = ft_strjoin("OLDPWD=", aux);
	free(aux);
	aux = getcwd(NULL, 0);
	temp_pwd[1] = ft_strjoin("PWD=", aux);
	free(aux);
	ft_export(temp_pwd);
	free_split(temp_pwd);
}

static char	*set_path(char *line)
{
	char	*aux;

	if (!line || line[0] == '\0' || !ft_strcmp(line, "~\0"))
		aux = get_env_value("HOME");
	else if (!ft_strncmp("-", line, 1))
		aux = get_env_value("OLDPWD");
	else
		aux = ft_strdup(line);
	return (aux);
}

int	ft_cd(char *line)
{
	char	*aux;
	int		chdir_;

	chdir_ = 0;
	aux = set_path(line);
	chdir_ = chdir(aux);
	if (chdir_ == -1)
	{
		if (!aux && line[0] == '-')
			ft_putstr_fd("IA_minishell: cd: OLDPWD not set\n", 2);
		else if (!aux)
			ft_putstr_fd("IA_minishell: cd: HOME not set\n", 2);
		else if (aux[0] != '\0')
			print_error(aux);
		free(aux);
		return (1);
	}
	change_pwd(getcwd(NULL, 0));
	free(aux);
	return (0);
}
