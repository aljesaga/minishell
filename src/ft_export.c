/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:06:51 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/30 16:53:07 by ioriola          ###   ########.fr       */
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
		if (ft_strncmp(id[0], aux->value, ft_strlen(id[0])) < 0)
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

	if (str[0] == '$' || str[0] == '*' || ft_isdigit(str[0]) == 1)
	{
		ft_puterror("export", str);
		return (1);
	}
	check = check_name(mini, str);
	if (check == 0)
		new_env(str, 1, mini);
	return (0);
}
