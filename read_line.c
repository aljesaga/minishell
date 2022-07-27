/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/27 21:20:28 by alsanche         ###   ########lyon.fr   */
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
		mini->l_exit = export(str[1], mini);
	else if (!ft_strncmp(str[0], "export\0", 7) && str[1] == NULL)
		export_sa(mini);
	else if (!ft_strncmp(str[0], "unset\0", 6) && str[1])
		unset(str[1], mini);
	else if (!ft_strncmp(str[0], "echo\0", 5))
		ft_echo(str, mini);
	else if (!ft_strncmp(str[0], "exit\0", 5) && (str[1] == NULL))
		exit (0);
	else if (!ft_strncmp(str[0], "env\0", 4))
		print_env(mini);
	else if (!ft_strncmp(str[0], "cd\0", 3))
		ft_cd(line);
	else if (!ft_strncmp(str[0], "pwd\0", 4))
		ft_pwd();
	free_split(str);
	return (0);
}
