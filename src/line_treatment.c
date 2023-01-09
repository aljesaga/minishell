/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:23:09 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/09 17:37:45 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	jump_quotes(char *line)
{
	int	i;

	i = -1;
	g_mini->quotes = 0;
	if (line[0] == 34 && line[1] == 34)
		return (0);
	while (line[++i])
	{
		if (line[i] == 39 && g_mini->quotes == 0)
			g_mini->quotes = 1;
		else if (line[i] == 39 && g_mini->quotes == 1)
		{
			g_mini->quotes = 0;
			return (i);
		}
		else if (line[i] == 34 && g_mini->quotes == 0)
			g_mini->quotes = 2;
		else if (line[i] == 34 && g_mini->quotes == 2)
		{
			g_mini->quotes = 0;
			return (i);
		}
	}
	return (0);
}

int	word_width(char *str)
{
	int	count;

	count = -1;
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	else if (!ft_strncmp(str, ">>", 2))
		return (2);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	else if (!ft_strncmp(str, "|", 1))
		return (1);
	else if (!ft_strncmp(str, ";", 1))
		return (1);
	while (str[++count] != '\0')
	{
		if (str[count] == 34 || str[count] == 39)
			count += jump_quotes(&str[count]);
		else if (str[count] == ' ' || str[count] == '|'
			|| str[count] == '<' || str[count] == '>' || str[count] == ';')
			break ;
	}
	return (count);
}

int	check_quotes(char *line)
{
	int	i;

	i = -1;
	g_mini->quotes = 0;
	if (line[0] == 34 && line[1] == 34)
		return (0);
	while (line[++i])
	{
		if (line[i] == 39 && g_mini->quotes == 0)
			g_mini->quotes = 1;
		else if (line[i] == 39 && g_mini->quotes == 1)
			g_mini->quotes = 0;
		else if (line[i] == 34 && g_mini->quotes == 0)
			g_mini->quotes = 2;
		else if (line[i] == 34 && g_mini->quotes == 2)
			g_mini->quotes = 0;
	}
	if (g_mini->quotes == 2 || g_mini->quotes == 1)
		return (-1);
	return (0);
}

void	ft_line_treatment(char *line)
{
	char	*aux;
	int		limit;
	int		j;

	j = 0;
	limit = 0;
	while (line[j] != '\0')
	{
		while (line[j] == ' ')
			j++;
		limit = word_width(&line[j]);
		aux = ft_substr(line, j, limit);
		add_segtion(aux, j);
		free(aux);
		j += limit;
	}
	assign_type();
}
