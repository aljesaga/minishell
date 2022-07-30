/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:18:06 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/30 16:29:46 by ioriola          ###   ########.fr       */
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
	while (aux && aux->next != NULL)
	{
		str[++i] = ft_strdup(aux->value);
		aux = aux->next;
	}
	str[++i] = NULL;
	return (str);
}
