/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/25 13:25:33 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	analyze_line(char *line, t_mshell *mini)
{
	char	**str;

	if (line[0] == '\0')
		return (0);
	str = ft_split(line, ' ');
	mini->fd_out = STDOUT_FILENO;
	if (!ft_strncmp(str[0], "export\0", 7) && str[1])
		mini->l_exit = export(ft_strup(str[1], ft_strlen(str[1])), mini);
	if (!ft_strncmp(str[0], "export\0", 7) && str[1] == NULL)
		export_sa(mini);
	if (!ft_strncmp(str[0], "unset\0", 6) && str[1])
		unset(str[1], mini);
	if (!ft_strncmp(str[0], "echo\0", 5))
		ft_echo(str, mini);
	if (!ft_strncmp(str[0], "exit\0", 5) && (str[1] == NULL))
		exit (0);
	if (!ft_strncmp(str[0], "env\0", 4))
		print_env(mini);
	if (!ft_strncmp(str[0], "cd\0", 3))
		ft_cd(line);
	free_split(str);
	return (1);
}
