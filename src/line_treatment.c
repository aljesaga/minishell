/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:23:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/24 18:49:59 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	word_width(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != 0)
	{
		if (str[count] == ' ')
			break ;
		count++;
	}
	return (count);
}

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

static int	ft_type(char *line, int limit)
{
 	if (!ft_strncmp(line, "<<", limit) == 0)
		return (2);
	else if (!ft_strncmp(line, ">>", limit) == 0)
		return (4);
	else if (!ft_strncmp(line, "<", limit) == 0)
		return (1);
	else if (!ft_strncmp(line, ">", limit) == 0)
		return (3);
	else if (!ft_strncmp(line, "|", limit) == 0)
		return (5);
	else
		return (6);
	
}

void	ft_line_treatment(char *line, t_mshell *mini)
{
	int	i;

	i = 0;
	if (check_quotes(line, mini) == -1)
	{
		printf("OPEN QUOTES");
		exit(1);
	}
	while (line[j] != 0)
	{
		if(line[j] == 34 || line[j] == 39)
			j += check_quotes(&line[j]);
		else
			j += word_width(&line[j]);
		if (ft_type(&line[j + 1], ) != 6)
	}
}
