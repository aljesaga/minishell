/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/28 13:42:05 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_comand(void)
{
	t_comand	*aux;

	while (g_mini->comands)
	{
		aux = g_mini->comands->next;
		free_split(g_mini->comands->comand);
		free(g_mini->comands);
		g_mini->comands->next = NULL;
		g_mini->comands = aux;
	}
}

void	free_sections(void)
{
	t_section	*aux;

	while (g_mini->sections)
	{
		aux = g_mini->sections->next;
		free(g_mini->sections->str);
		free(g_mini->sections);
		g_mini->sections->next = NULL;
		g_mini->sections = aux;
	}
}

int	analyze_line(char *line)
{
	char		*str;

	if (!line || line[0] == '\0')
		return (0);
	g_mini->a_error = 0;
	if (check_quotes(line) == 1)
	{
		printf("final quotes not found");
		g_mini->a_error = 258;
	}
	if (g_mini->a_error != 258)
	{
		str = ft_strtrim(line, " ");
		ft_line_treatment(str);
		if (g_mini->a_error != 258)
		{
			set_up_comand();
			if (g_mini->n_com > 0)
				g_mini->a_error = ft_execv();
		}
		free_comand();
		free_sections();
		free(str);
	}
	return (g_mini->a_error);
}
