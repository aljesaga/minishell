/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:34:11 by ioriola           #+#    #+#             */
/*   Updated: 2022/09/18 15:44:03 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
unset
	Unset values and attributes of shell variables and functions.
		- With no options
*/

void	unset_mini(t_mshell *mini)
{
	t_env	*aux;
	t_env	*temp;

	aux = mini->env;
	while (aux)
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
			mini->n_env--;
			break ;
		}
		aux = aux->next;
	}
}

void	ft_unset(char *str, t_mshell *mini)
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
			free(temp->value);
			free(temp);
			mini->n_env--;
			break ;
		}
		aux = aux->next;
	}
	free(id);
}
