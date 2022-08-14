/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:06:51 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/14 15:18:05 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	export
	Set export attribute for shell variables.
		- With no options
*/

static int	check_name(t_mshell *mini, char *str)
{
	t_env	*aux;
	char	**id;

	id = ft_split(str, '=');
	aux = mini->env;
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

int	ft_export(char *str, t_mshell *mini)
{
	int		check;
	int		i;

	i = 0;
	if (str[0] == 92)
		i++;
	if (str[i] == '$' || str[i] == '*' || ft_isdigit(str[i]) == 1)
	{
		ft_puterror("export", &str[i]);
		return (1);
	}
	if (i == 1)
	{
		check = check_name(mini, &str[1]);
		if (check == 0)
			new_env(&str[1], 1, mini);
	}
	else
	{
		check = check_name(mini, str);
		if (check == 0)
			new_env(str, 1, mini);
	}
	return (0);
}
