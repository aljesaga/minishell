/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:23:14 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/28 13:58:52 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(char *env_name)
{
	t_env	*temp_env;
	char	*value;
	int		len;

	len = ft_strlen(env_name);
	temp_env = g_mini->env;
	while (temp_env->value)
	{
		if (!ft_strncmp(temp_env->value, env_name, len))
		{
			value = ft_strdup(ft_strchr(temp_env->value, '=') + 1);
			return (value);
		}
		if (!temp_env->next)
			break ;
		else
			temp_env = temp_env->next;
	}
	return (NULL);
}
