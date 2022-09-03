/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:47:51 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/03 18:24:05 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_chr(char *str, t_mshell *mini)
{
	char	*aux;
	char	*end;
	char	*temp;
	int		s;
	int		i;

	while (str[++i])
	{
		if (str[i] == '$' && ft_isalpha(str[i + 1]) == 1)
		{
			s = word_width(&str[++i]);
			aux = ft_substr(&str[i], 0, s);
			temp = ft_str;
		}
		else
			end[i] = str[i];
	}
}

char	*str_expand(char *str)
{
	char	*end;
	char	*aux;
	int		s;
	int		i;

	i = -1;
	s = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '$')
			s++;
	}
	if (s == 0)
		return (ft_strdup(str));
	end = malloc(sizeof(char) * i + 1);
	i = -1;
	
}
