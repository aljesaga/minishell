/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:06:51 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/27 21:44:43 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_sa(t_mshell *mini)
{
	char	**export;
	char	*aux;
	int		y;
	int		x;

	export = env_2_str(mini);
	y = -1;
	while (export[++y])
	{
		x = y;
		while (export[++x])
		{
			if (ft_strcmp(export[y], export[x]) > 0)
			{
				aux = export[y];
				export[y] = export[x];
				export[x] = aux;
			}
		}
	}
	y = -1;
	while (export[++y])
		printf("---->%s\n", export[y]);
	free_split(export);
}

void	shlvlup(t_mshell *mini)
{
	t_env	*aux;
	char	*chg;
	char	*temp;
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
			temp = ft_strjoin("SHLVL=", num);
			export(temp, mini);
			free(temp);
			free(num);
			free(chg);
		}
		aux = aux->next;
	}
}

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

int	export(char *str, t_mshell *mini)
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
