/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:04:38 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/30 16:44:09 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	env
	Displays and modifies environment variables.
		- With no options or arguments
*/

static void	add_env(t_env *newenv, t_mshell *mini)
{
	t_env	*temp;

	temp = mini->env;
	if (temp->next == NULL)
		temp->next = newenv;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newenv;
	}
}

void	new_env(char *str, int num, t_mshell *mini)
{
	t_env	*newenv;

	newenv = malloc(sizeof(t_env));
	if (!newenv)
		exit (127);
	newenv->value = ft_strdup(str);
	newenv->next = NULL;
	mini->n_env++;
	if (num == 0)
		mini->env = newenv;
	else
		add_env(newenv, mini);
}

int	env_collec(char **env, t_mshell *mini)
{
	int		i;

	if (env == NULL)
		return (1);
	mini->n_env = 0;
	i = -1;
	while (env[++i])
		new_env(env[i], i, mini);
	return (0);
}

void	ft_env(t_mshell *mini)
{
	t_env	*temp;
	char	*aux;

	temp = mini->env;
	while (temp != NULL)
	{
		aux = ft_strchr(temp->value, '=');
		if (aux != NULL)
		{
			ft_putstr_fd(temp->value, mini->fd_out);
			ft_putchar_fd('\n', mini->fd_out);
		}
		temp = temp->next;
	}
	ft_putstr_fd("_=/Users/alsanche/minishell/env\n", mini->fd_out);
}
