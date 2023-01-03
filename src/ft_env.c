/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:04:38 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/03 15:36:33 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	env
	Displays and modifies environment variables.
		- With no options or arguments
*/

static void	add_env(t_env *newenv)
{
	t_env	*temp;

	temp = g_mini->env;
	if (temp->next == NULL)
		temp->next = newenv;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newenv;
	}
}

void	new_env(char *str, int num)
{
	t_env	*newenv;

	newenv = malloc(sizeof(t_env));
	if (!newenv)
		exit (1);
	newenv->value = ft_strdup(str);
	newenv->next = NULL;
	g_mini->n_env++;
	if (num == 0)
		g_mini->env = newenv;
	else
		add_env(newenv);
}

int	env_collec(char **env)
{
	int		i;

	if (env == NULL)
		return (1);
	g_mini->n_env = 0;
	i = -1;
	while (env[++i] != NULL)
		new_env(env[i], i);
	return (0);
}

int	ft_env(t_comand *com)
{
	t_env	*temp;
	char	*aux;

	temp = g_mini->env;
	if (!temp || com)
		return (1);
	if (com->comand[1])
	{
		dprintf(2, "env: %s: no such file or directory\n", com->comand[1]);
		return (1);
	}
	while (temp != NULL)
	{
		aux = ft_strchr(temp->value, '=');
		if (aux != NULL)
		{
			ft_putstr_fd(temp->value, com->fd_out);
			ft_putchar_fd('\n', com->fd_out);
		}
		temp = temp->next;
	}
	return (0);
}
