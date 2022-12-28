/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:06:51 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/28 13:52:11 by alsanche         ###   ########lyon.fr   */
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

int	ft_export(char **comand)
{
	int		check;
	char	*str;
	int		i;
	int		x;

	i = 0;
	while (comand[++i])
	{
		str = comand[i];
		x = 0;
		if (str[0] == 92)
			x++;
		if (str[x] == '$' || str[x] == '*' || ft_isdigit(str[x]) == 1)
		{
			ft_puterror("export", &str[x]);
			return (1);
		}
		check = check_name(&str[x]);
		if (check == 0)
		{
			new_env(&str[x], 1);
		}
	}
	return (0);
}
