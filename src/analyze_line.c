/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/30 17:24:07 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	analyze_line(char *line, t_mshell *mini)
{
	char	**str;

	if (line[0] == '\0')
		return (0);
	str = ft_split(line, ' ');
	mini->fd_out = STDOUT_FILENO;
	if (!ft_strncmp(str[0], "export\0", 7) && str[1])
		mini->l_exit = ft_export(str[1], mini);
	else if (!ft_strncmp(str[0], "export\0", 7) && str[1] == NULL)
		ft_export_no_args(mini);
	else if (!ft_strncmp(str[0], "unset\0", 6) && str[1])
		ft_unset(str[1], mini);
	else if (!ft_strncmp(str[0], "echo\0", 5))
		ft_echo(str, mini);
	else if (!ft_strncmp(str[0], "exit\0", 5) && (str[1] == NULL))
		exit (0);
	else if (!ft_strncmp(str[0], "env\0", 4))
		ft_env(mini);
	else if (!ft_strncmp(str[0], "cd\0", 3))
		ft_cd(line, mini);
	else if (!ft_strncmp(str[0], "pwd\0", 4))
		ft_pwd();
	free_split(str);
	return (0);
}