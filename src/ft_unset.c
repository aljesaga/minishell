/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:34:11 by ioriola           #+#    #+#             */
/*   Updated: 2023/01/25 12:49:04 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
unset
	Unset values and attributes of shell variables and functions.
		- With no options
*/

void	unset_mini(void)
{
	t_env	*aux;
	t_env	*temp;

	aux = g_mini->env;
	while (aux && aux->next)
	{
		if (aux->next->value[0] == '_' && aux->next->value[1] == '=')
		{
			temp = aux->next;
			if (temp->next == NULL)
				aux->next = NULL;
			else
				aux->next = temp->next;
			free(temp->value);
			free(temp);
			g_mini->n_env--;
			break ;
		}
		aux = aux->next;
	}
}

int	check_unset(t_env *aux, char *id)
{
	t_env	*temp;

	while (aux && aux->next)
	{
		if (!ft_strncmp(aux->next->value, id, ft_strlen(id) + 1))
		{
			temp = aux->next;
			if (temp->next == NULL)
				aux->next = NULL;
			else
				aux->next = temp->next;
			free(temp->value);
			free(temp);
			g_mini->n_env--;
			return (0);
		}
		aux = aux->next;
	}
	return (1);
}	

int	ft_unset(char *str)
{
	t_env	*aux;
	char	*id;
	int		out;

	aux = g_mini->env;
	id = ft_strjoin(str, "=");
	out = check_unset(aux, id);
	if (out == 1)
	{
		free(id);
		id = ft_strjoin(str, "\0");
		out = check_unset(aux, id);
	}
	free(id);
	return (out);
}
