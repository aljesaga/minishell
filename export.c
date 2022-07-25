/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:06:51 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/25 13:39:17 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvlup(t_mshell *mini)
{
	t_env	*aux;
	char	*chg;
	char	*num;
	char	*shl;
	int		i;

	aux = mini->env;
	i = 0;
	while (aux)
	{
		if (!ft_strncmp(aux->value, "SHLVL=", 6))
		{
			while (aux->value[i] != '=')
				i++;
			chg = ft_substr(aux->value, i + 1, INT_MAX);
			num = ft_itoa(ft_atoi(chg) + 1);
			shl = aux->value;
			export(ft_strjoin("SHLVL=", num), mini);
			if (ft_strncmp(chg, "1\0", 2))
				free(shl);
			free(num);
			free(chg);
		}
		aux = aux->next;
	}
}

int	export(char *str, t_mshell *mini)
{
	t_env	*aux;
	char	**id;
	int		check;

	if (!str || str == NULL || ft_strchr(str, '=') == NULL)
		return (0);
	aux = mini->env;
	id = ft_split(str, '=');
	check = 0;
	while (aux)
	{
		if (!ft_strncmp(aux->value, id[0], ft_strlen(id[0])))
		{
			aux->value = str;
			check = aux->change++;
		}
		aux = aux->next;
	}
	free_split(id);
	if (check == 0)
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
			mini->n_env--;
			break ;
		}
		aux = aux->next;
	}
	free(id);
}
