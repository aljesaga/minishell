/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:23:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/23 18:43:48 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	word_width(char *str, t_mshell *mini)
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
	while (str[++count] != '\0')
	{
		if (str[count] == 34 || str[count] == 39)
			count += check_quotes(&str[count], mini);
		else if (str[count] == ' ' || str[count] == '|'
			|| str[count] == '<' || str[count] == '>')
			break ;
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

void	ft_line_treatment(char *line, t_mshell *mini)
{
	char	*aux;
	int		limit;
	int		j;

	j = 0;
	limit = 0;
	if (check_quotes(line, mini) == -1)
	{
		printf("OPEN QUOTES");
		exit(1);
	}
	while (line[j] != '\0')
	{
		while (line[j] == ' ')
			j++;
		if (line[j] == 34 || line[j] == 39)
			limit = check_quotes(&line[j], mini) + 1;
		else
			limit = word_width(&line[j], mini);
		aux = ft_substr(line, j, limit);
		add_segtion(aux, mini, j);
		free(aux);
		j += limit;
	}
	assign_type(mini);
}
