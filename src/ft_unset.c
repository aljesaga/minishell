/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:34:11 by ioriola           #+#    #+#             */
/*   Updated: 2022/07/30 16:34:50 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
unset
	Unset values and attributes of shell variables and functions.
		- With no options
*/

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
			free(temp);
			mini->n_env--;
			break ;
		}
		aux = aux->next;
	}
	free(id);
}