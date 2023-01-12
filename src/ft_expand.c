/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:47:51 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/12 15:46:26 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	expand_name(char *str)
{
	int	count;

	count = -1;
	while (str[++count])
	{
		if (str[count + 1] == '?')
		{
			count++;
			break ;
		}
		if ((str[count + 1] >= 32 && str[count + 1] <= 47)
			|| (str[count + 1] >= 58 && str[count + 1] <= 64)
			|| (str[count + 1] >= 91 && str[count + 1] <= 96)
			|| (str[count + 1] >= 123))
			break ;
	}
	return (count);
}

static char	*ft_strjoinchr(char const *s1, char s2)
{
	char	*new;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * ft_strlen(s1) + 2);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = s2;
	new[i++] = '\0';
	return (new);
}

static char	*expand_chr(char *str, char *end, int s)
{
	char	*aux;
	char	*temp;

	aux = ft_substr(str, 0, s);
	if (str[0] == '?' && str[1] == '\0')
		temp = ft_itoa(g_mini->l_exit);
	else
		temp = get_env_value(aux);
	free(aux);
	if (temp != NULL)
	{
		aux = end;
		end = ft_strjoin(aux, temp);
		free(temp);
		free(aux);
	}
	return (end);
}

char	*str_expand(char *str)
{
	char	*end;
	char	*aux;
	int		i[2];

	i[0] = -1;
	end = ft_strdup("");
	while (str[++i[0]])
	{
		if (str[i[0]] == '$' && str[i[0] - 1] != 92
			&& (ft_isalpha(str[i[0] + 1]) == 1 || str[i[0] + 1] == '?'))
		{
			i[1] = expand_name(&str[++i[0]]);
			end = expand_chr(&str[i[0]], end, i[1]);
			i[0] += i[1];
			if (str[i[0]] == '\0')
				break ;
		}
		else
		{
			aux = end;
			end = ft_strjoinchr(aux, str[i[0]]);
			free(aux);
		}
	}
	return (end);
}
