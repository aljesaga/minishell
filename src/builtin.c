/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:33:43 by ioriola           #+#    #+#             */
/*   Updated: 2022/08/10 14:13:44 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

void	run_builtin(char **args, char *line, t_mshell *mini)
{
	if (!ft_strncmp(args[0], "export\0", 7) && args[1])
		mini->l_exit = ft_export(args[1], mini);
	else if (!ft_strncmp(args[0], "export\0", 7) && args[1] == NULL)
		ft_export_no_args(mini);
	else if (!ft_strncmp(args[0], "unset\0", 6) && args[1])
		ft_unset(args[1], mini);
	else if (!ft_strncmp(args[0], "echo\0", 5))
		ft_echo(args, mini);
	else if (!ft_strncmp(args[0], "exit\0", 5) && (args[1] == NULL))
		exit (0);
	else if (!ft_strncmp(args[0], "env\0", 4))
		ft_env(mini);
	else if (!ft_strncmp(args[0], "cd\0", 3))
		ft_cd(line, mini);
	else if (!ft_strncmp(args[0], "pwd\0", 4))
		ft_pwd(mini);
}
