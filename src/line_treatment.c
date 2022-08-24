/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:23:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/24 18:36:40 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_quotes(char *line, t_mshell *mini)
{
	int	i;

	i = -1;
	mini->quotes = 0;
	while (line[++i] != '\0')
	{
		if (line[i] == 39 && mini->quotes == 0)
			mini->quotes = 1;
		else if (line[i] == 39 && mini->quotes == 1)
		{
			mini->quotes = 0;
			return (i);
		}
		else if (line[i] == 34 && mini->quotes == 0)
			mini->quotes = 2;
		else if (line[i] == 34 && mini->quotes == 2)
		{
			mini->quotes = 0;
			return (i);
		}
	}
	if (mini->quotes == 2 || mini->quotes == 1)
		return (-1);
	return (0);
}

static void	add_section(char *line, t_mshell *mini, int count)
{
	t_section	*new;
	t_section	*aux;

	new = malloc(sizeof(t_section));
	if (!new)
		exit(1);
	new->str = ft_substr(line, 0, count);
	new->next = NULL;
	if (line[0] == '<' || line[0] == '>')
		new->type = 3;
	else
		new->type = 1;
	aux = mini->sections;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new;
}

static void	sections(char *line, t_mshell *mini)
{
	int	i;
	int	j;
	int	count;

	j = -1;
	while (line[++j] != '\0')
	{
		i = j;
		count = 0;
		while (line[++i] != '\0')
		{
			if (line[i] == 34 || line[i] == 39)
				i += check_quotes(&line[i], mini);
			if (mini->quotes == 0)
				if (line[i] == ' ' || line[i] == '|'
					|| line[i] == '<' || line[i] == '>')
					break ;
			count++;
		}
		add_section(&line[j], mini, count);
		j = i;
	}
}

void	ft_line_treatment(char *line, t_mshell *mini)
{
	if (check_quotes(line, mini) == -1)
	{
		printf("OPEN QUOTES");
		exit(1);
	}
	sections(line, mini);
}
