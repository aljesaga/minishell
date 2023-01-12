/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:23:14 by ioriola           #+#    #+#             */
/*   Updated: 2023/01/12 14:24:27 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(char *env_name)
{
	t_env	*temp_env;
	char	*aux;
	char	*value;

	aux = ft_strjoin(env_name, "=");
	temp_env = g_mini->env;
	while (temp_env->value)
	{
		if (!ft_strncmp(temp_env->value, aux, ft_strlen(aux)))
		{
			value = ft_strdup(ft_strchr(temp_env->value, '=') + 1);
			free(aux);
			return (value);
		}
		if (!temp_env->next)
			break ;
		else
			temp_env = temp_env->next;
	}
	free(aux);
	return (NULL);
}
