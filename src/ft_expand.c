/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:47:51 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/24 15:01:43 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	expand_name(char *str)
{
	int	count;

	count = 0;
	while (str[++count] != '\0')
	{
		if (str[count + 1] == '?')
		{
			count++;
			break ;
		}
		else if (str[count + 1] == 34 || str[count + 1] == 39
			|| str[count + 1] == '$' || str[count + 1] == '\n')
			break ;
		else if (str[count + 1] == ' ' || str[count + 1] == '|'
			|| str[count + 1] == '<' || str[count + 1] == '>')
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

static char	*expand_chr(char *str, char *end, int s, t_mshell *mini)
{
	char	*aux;
	char	*temp;

	aux = ft_substr(str, 0, s);
	if (str[0] == '?' && str[1] == '\0')
		temp = ft_itoa(mini->l_exit);
	else
		temp = get_env_value(aux, mini);
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

char	*str_expand(char *str, t_mshell *mini)
{
	char	*end;
	char	*aux;
	int		s;
	int		i;

	i = -1;
	end = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) == 1 || str[i + 1] == '?'))
		{
			s = expand_name(&str[++i]);
			end = expand_chr(&str[i], end, s, mini);
			i += s;
			if (str[i] == '\0')
				break ;
		}
		else
		{
			aux = end;
			end = ft_strjoinchr(aux, str[i]);
			free(aux);
		}
	}
	return (end);
}
