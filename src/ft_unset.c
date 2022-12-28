/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:34:11 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/28 13:58:28 by alsanche         ###   ########lyon.fr   */
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

int	ft_unset(char *str)
{
	t_env	*aux;
	t_env	*temp;
	char	*id;

	aux = g_mini->env;
	id = ft_strjoin(str, "=");
	while (aux && aux->next)
	{
		if (!ft_strncmp(aux->next->value, id, ft_strlen(id)))
		{
			temp = aux->next;
			if (temp->next == NULL)
				aux->next = NULL;
			else
				aux->next = temp->next;
			free(temp->value);
			free(temp);
			g_mini->n_env--;
			free(id);
			return (0);
		}
		aux = aux->next;
	}
	free(id);
	return (1);
}
