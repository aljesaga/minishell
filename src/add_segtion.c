/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_segtion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:35:08 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/11 16:42:55 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*clean(char *str, t_mshell *mini)
{
	char	*aux;
	int		j;
	int		i;

	aux = malloc(sizeof(char) * ((ft_strlen(str) - 2) + 1));
	i = -1;
	j = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == 39 && mini->quotes == 0)
			mini->quotes = 1;
		else if (str[i] == 39 && mini->quotes == 1)
			mini->quotes = 0;
		else if (str[i] == 34 && mini->quotes == 0)
			mini->quotes = 2;
		else if (str[i] == 34 && mini->quotes == 2)
			mini->quotes = 0;
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

static char	*clean_expand(char *str, t_mshell *mini, t_section *new)
{
	char	*aux;
	char	*end;

	new->here_expand = shr_quotes(str);
	if (new->here_expand == 0 || new->here_expand == 2)
	{
		aux = str_expand(str, mini);
		if (new->here_expand == 0)
			return (aux);
		else
		{
			end = clean(aux, mini);
			free(aux);
			return (end);
		}
	}
	else if (new->here_expand != 0)
	{
		end = clean(str, mini);
		return (end);
	}
	return (str);
}

void	add_segtion(char *str, t_mshell *mini, int check)
{
	t_section	*new;
	t_section	*aux;

	new = malloc(sizeof(t_section));
	if (!new)
		printf("Memory Error");
	new->str = clean_expand(str, mini, new);
	new->next = NULL;
	if (check == 0)
		mini->sections = new;
	else
	{
		aux = mini->sections;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}
