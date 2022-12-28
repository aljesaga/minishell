/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_segtion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:35:08 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/28 13:40:37 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*clean(char *str)
{
	char	*aux;
	int		j;
	int		i;

	aux = malloc(sizeof(char) * ((ft_strlen(str) - 2) + 1));
	i = -1;
	j = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == 39 && g_mini->quotes == 0)
			g_mini->quotes = 1;
		else if (str[i] == 39 && g_mini->quotes == 1)
			g_mini->quotes = 0;
		else if (str[i] == 34 && g_mini->quotes == 0)
			g_mini->quotes = 2;
		else if (str[i] == 34 && g_mini->quotes == 2)
			g_mini->quotes = 0;
		else
			aux[++j] = str[i];
	}
	aux[++j] = '\0';
	return (aux);
}

static int	shr_quotes(char *str)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (str[++i] && quotes == 0)
	{
		if (str[i] == 34)
			quotes = 2;
		else if (str[i] == 39)
			quotes = 1;
	}
	return (quotes);
}

static char	*clean_expand(char *str, t_section *new)
{
	char	*aux;
	char	*end;

	new->here_expand = shr_quotes(str);
	if (new->here_expand == 0 || new->here_expand == 2)
	{
		aux = str_expand(str);
		if (new->here_expand == 0)
			return (aux);
		else
		{
			end = clean(aux);
			free(aux);
			return (end);
		}
	}
	else if (new->here_expand != 0)
	{
		end = clean(str);
		return (end);
	}
	return (str);
}

void	add_segtion(char *str, int check)
{
	t_section	*new;
	t_section	*aux;
	int			i;

	new = malloc(sizeof(t_section));
	if (!new)
		printf("Memory Error");
	new->str = clean_expand(str, new);
	new->next = NULL;
	i = 0;
	if (check == 0)
	{
		g_mini->sections = new;
		g_mini->sections->num = i;
	}
	else
	{
		aux = g_mini->sections;
		while (aux->next != NULL)
		{
			aux = aux->next;
			i++;
		}
		aux->next = new;
	}
}
