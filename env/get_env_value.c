/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:23:14 by ioriola           #+#    #+#             */
/*   Updated: 2022/07/29 09:26:58 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Busca en la lista de "t_env" y devuelve el valor de la variable que le pidas.
Si no la encuentra devuelve NULL.

Ejemplo:
{
	char *pwd;
	pwd = get_env_value("PWD", mini);
	// pwd = "/Users/alsanche/minishell/"
}
*/

char	*get_env_value(char *env_name, t_mshell *mini)
{
	t_env	*temp_env;
	char	*value;
	int		len;

	len = ft_strlen(env_name);
	temp_env = mini->env;
	while (temp_env->value)
	{
		value = ft_strnstr(temp_env->value, env_name, len);
		if (value)
		{
			value += 1 + len;
			return (value);
		}
		if (!temp_env->next)
			break ;
		else
			temp_env = temp_env->next;
	}
	return (NULL);
}
