/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:18:06 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/18 13:33:37 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*str_path(char **enpv)
{
	int	i;

	i = 0;
	if (!enpv || *enpv == NULL)
		return (NULL);
	while (enpv[i])
	{
		if (enpv[i][0] == 'P' && enpv[i][1] == 'A'
			&& enpv[i][2] == 'T' && enpv[i][3] == 'H')
			return (enpv[i]);
		i++;
	}
	return (NULL);
}

char	**find_path(char **enpv)
{
	char	**gps;
	char	*path;
	char	*aux;
	int		i;

	path = str_path(enpv);
	if (!path)
		return (NULL);
	i = -1;
	gps = ft_split(path, ':');
	while (gps[++i])
	{
		aux = gps[i];
		gps[i] = ft_strjoin(aux, "/");
		free(aux);
	}
	return (gps);
}

char	**env_2_str(t_mshell *mini)
{
	int		i;
	t_env	*aux;
	char	**str;

	i = -1;
	aux = mini->env;
	str = malloc(sizeof(char *) * mini->n_env + 1);
	if (!str)
		return (NULL);
	while (aux)
	{
		str[++i] = ft_strdup(aux->value);
		aux = aux->next;
	}
	str[++i] = NULL;
	return (str);
}
