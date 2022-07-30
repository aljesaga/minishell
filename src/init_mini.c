/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:03:58 by ioriola           #+#    #+#             */
/*   Updated: 2022/07/30 17:04:11 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_mshell	*init_mini(char **env)
{
	t_mshell	*mini;

	mini = malloc(sizeof(t_mshell));
	if (!mini)
		exit (127);
	mini->fd_out = STDOUT_FILENO;
	mini->l_exit = 0;
	env_collec(env, mini);
	shlvlup(mini);
	return (mini);
}