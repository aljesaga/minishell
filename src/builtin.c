/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:33:43 by ioriola           #+#    #+#             */
/*   Updated: 2022/09/18 14:52:15 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "export") || !ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

int	run_builtin(t_comand *com, t_mshell *mini)
{
	if (!ft_strncmp(com->comand[0], "export\0", 7) && com->comand[1])
		mini->l_exit = ft_export(com->comand, mini);
	else if (!ft_strncmp(com->comand[0], "export\0", 7))
		ft_export_no_args(mini);
	else if (!ft_strncmp(com->comand[0], "unset\0", 6) && com->comand[1])
		ft_unset(com->comand[1], mini);
	else if (!ft_strncmp(com->comand[0], "echo\0", 5))
		mini->l_exit = ft_echo(com);
	else if (!ft_strncmp(com->comand[0], "exit\0", 5) && com->comand[1] == NULL)
		exit (0);
	else if (!ft_strncmp(com->comand[0], "env\0", 4))
		ft_env(mini);
	else if (!ft_strncmp(com->comand[0], "cd\0", 3))
		mini->l_exit = ft_cd(com->comand[1], mini);
	else if (!ft_strncmp(com->comand[0], "pwd\0", 4))
		mini->l_exit = ft_pwd(com);
	return (mini->l_exit);
}
