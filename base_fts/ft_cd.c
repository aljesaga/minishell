/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:04:13 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/29 09:59:45 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("Failed to change directory: %s\n", strerror(errno));
		return (1);
	}
	export(ft_strjoin("OLDPWD=", temp_pwd), mini);
	export(ft_strjoin("PWD=", getcwd(NULL, 0)), mini);

	// if (line[0] == '\0')
	// 	write(1, "/home/mi_usuario\n", 18);
	// else if (line[0] == '.' && line[1] == '.')
	// {
	// 	if (line[2] == '/')
	// 		write(1, "/anterior/carpeta_en_ruta_anterior\n", 36);
	// 	else
	// 		write(1, "/ahora_aqui/actual\n", 20);
	// }
	// else if (line)
	// {
	// 	write(1, "/actual/", 9);
	// 	printf("%s\n", line);
	// }
	// else
	// 	write(1, "ERROR\n", 6);
	return (0);
}
