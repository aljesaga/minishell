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

int	ft_len2chr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] || str[i] != c)
	{
		i++;
	}	
	return  (i);
}

void	export_sa(t_mshell *mini)
{
	char	**export;
	char	*aux;
	int		y;
	int		x[2];
	
	export = env_2_str(mini);
	y = -1;
	while (export[++y])
	{
		x[0] = y + 1;
		while (export[x[0]])
		{
			if (export[x[0]] <= export[y])
			{
				x[1] = 0;
				while(x[1] <= ft_len2chr(export[y], '='))
				{
					if (export[x[0]][x[1]] < export[y][x[1]])
					{
						aux = export[y];
						export[y] = export[x[0]];
						export[x[0]] = aux;
					}
					x[1]++;
				}
				x[0]++;
			}
		}

	}
	y = -1;
	while (export[++y])
	{
		printf("---->%s\n", export[y]);
	}
}


void	shlvlup(t_mshell *mini)
{
	t_env	*aux;
	char	*chg;
	char	*num;
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
			export(ft_strjoin("SHLVL=", num), mini);
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
			free(aux->value);
			aux->value = ft_strdup(str);
			check = 1;
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
