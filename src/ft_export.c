/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:06:51 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/12 15:12:34 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	export
	Set export attribute for shell variables.
		- With no options
*/

int	check_name(char *str)
{
	t_env	*aux;
	char	**id;

	id = ft_split(str, '=');
	aux = g_mini->env;
	while (aux)
	{
		if (!ft_strncmp(id[0], aux->value, ft_strlen(id[0])))
		{
			free(aux->value);
			aux->value = ft_strdup(str);
			free_split(id);
			return (1);
		}
		aux = aux->next;
	}
	free_split(id);
	return (0);
}

static int	parce(char	*str)
{
	if (str == NULL || str[0] == '\0' || str[0] == '$' || str[0] == '*'
		|| ft_isdigit(str[0]) == 1)
	{
		ft_puterror("export", &str[0]);
		g_mini->l_exit = 1;
		return (1);
	}
	return (0);
}

int	ft_export(char **comand)
{
	int		check;
	char	*str;
	int		i;
	int		r;
	int		x;

	i = 0;
	while (comand[++i])
	{
		x = 0;
		str = comand[i];
		if (str[0] == 92)
			x++;
		r = parce(&str[x]);
		if (r == 0)
		{
			check = check_name(&str[x]);
			if (check == 0)
				new_env(&str[x], 1);
		}
	}
	return (g_mini->l_exit);
}
