/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvlup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:45:55 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/28 14:01:02 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shlvlup(void)
{
	t_env	*aux;
	char	*chg;
	char	*temp;
	char	*num;
	int		i;

	aux = g_mini->env;
	i = 0;
	while (aux)
	{
		if (!ft_strncmp(aux->value, "SHLVL=", 6))
		{
			while (aux->value[i] != '=')
				i++;
			chg = ft_substr(aux->value, i + 1, INT_MAX);
			num = ft_itoa(ft_atoi(chg) + 1);
			temp = ft_strjoin("SHLVL=", num);
			check_name(temp);
			free(temp);
			free(num);
			free(chg);
		}
		aux = aux->next;
	}
}
