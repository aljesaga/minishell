/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:18:06 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/14 14:31:29 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**env_2_str(t_mshell *mini)
{
	int		i;
	t_env	*aux;
	char	**str;

	i = -1;
	aux = mini->env;
	str = malloc(sizeof(char *) * mini->n_env);
	if (!str)
		return (NULL);
	while (aux && aux != NULL)
	{
		str[++i] = ft_strdup(aux->value);
		aux = aux->next;
	}
	str[++i] = NULL;
	return (str);
}
