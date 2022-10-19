/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 11:33:43 by ioriola           #+#    #+#             */
/*   Updated: 2022/10/19 18:49:20 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd\0", 3) || !ft_strncmp(str, "echo\0", 5))
		return (1);
	if (!ft_strncmp(str, "env\0", 4) || !ft_strncmp(str, "exit\0", 5))
		return (1);
	if (!ft_strncmp(str, "export\0", 7) || !ft_strncmp(str, "pwd\0", 4))
		return (1);
	if (!ft_strncmp(str, "unset\0", 6))
		return (1);
	return (0);
}

int	run_builtin(t_comand *com, t_mshell *mini)
{
	if (!ft_strncmp(com->comand[0], "export\0", 7) && com->comand[1])
		mini->l_exit = ft_export(com->comand, mini);
	else if (!ft_strncmp(com->comand[0], "export\0", 7))
		mini->l_exit = ft_export_no_args(com, mini);
	else if (!ft_strncmp(com->comand[0], "unset\0", 6) && com->comand[1])
		mini->l_exit = ft_unset(com->comand[1], mini);
	else if (!ft_strncmp(com->comand[0], "echo\0", 5))
		mini->l_exit = ft_echo(com);
	else if (!ft_strncmp(com->comand[0], "exit\0", 5))
		ft_exit(com, mini);
	else if (!ft_strncmp(com->comand[0], "env\0", 4))
		mini->l_exit = ft_env(com, mini);
	else if (!ft_strncmp(com->comand[0], "cd\0", 3))
		mini->l_exit = ft_cd(com->comand[1], mini);
	else if (!ft_strncmp(com->comand[0], "pwd\0", 4))
		mini->l_exit = ft_pwd(com);
	return (mini->l_exit);
}
