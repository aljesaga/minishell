/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:06:51 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/25 11:03:57 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_value(t_env *aux, char *value)
{
	
}

int	export(char *str, t_mshell *mini)
{
	t_env	*aux;
	char	**id;

	if (!str || str == NULL || ft_strchr(str, '=') == NULL)
		return (0);
	aux = mini->env;
	id = ft_splid(str, "=");
	while (aux)
	{
		if (!ft_strncmp(aux->value, id[0], ft_strlen(id[0])))
			ft_change_value(aux, id[1]);
		aux = aux->next;
	}
	new_env(str, 1, mini);
	return (0);
}

void	unset(char *str, t_mshell *mini)
{
	t_env	*aux;
	t_env	*temp;
	char	*id;

	aux = mini->env;
	id = ft_strjoin(str, "=");
	while (aux)
	{
		if (!ft_strncmp(aux->next->value, id, ft_strlen(id)))
		{
			temp = aux->next;
			if (temp->next == NULL)
				aux->next = NULL;
			else
				aux->next = temp->next;
			free(temp);
			break ;
		}
		aux = aux->next;
	}
	free(id);
}
