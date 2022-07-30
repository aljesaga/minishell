/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:04:13 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/30 16:39:06 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	cd
	Change the shell working directory.
		- With only a relative or absolute path
*/

int		ft_cd(char *line, t_mshell *mini)
{
	char *temp_pwd;
	int chdir_;

	line += 3;
	line = ft_strtrim(line, " ");
	temp_pwd = get_env_value("PWD", mini);
	chdir_ = chdir(line);
	if (chdir_ == -1)
	{
		printf("cd: %s: %s\n", strerror(errno), line);
		return (1);
	}
	ft_export(ft_strjoin("OLDPWD=", temp_pwd), mini);
	ft_export(ft_strjoin("PWD=", getcwd(NULL, 0)), mini);
	return (0);
}
