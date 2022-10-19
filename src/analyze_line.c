/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/19 16:14:36 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_comand(t_mshell *mini)
{
	t_comand	*aux;

	while (mini->comands)
	{
		aux = mini->comands->next;
		free_split(mini->comands->comand);
		free(mini->comands);
		mini->comands->next = NULL;
		mini->comands = aux;
	}
}

void	free_sections(t_mshell *mini)
{
	t_section	*aux;

	while (mini->sections)
	{
		aux = mini->sections->next;
		free(mini->sections->str);
		free(mini->sections);
		mini->sections->next = NULL;
		mini->sections = aux;
	}
}

int	analyze_line(char *line, t_mshell *mini)
{
	char		*str;

	if (!line || line[0] == '\0')
		return (0);
	mini->a_error = 0;
	if (check_quotes(line, mini) == 1)
	{
		printf("final quotes not found");
		mini->a_error = 258;
	}
	if (mini->a_error != 258)
	{
		str = ft_strtrim(line, " ");
		ft_line_treatment(str, mini);
		if (mini->a_error != 258)
		{
			set_up_comand(mini);
			if (mini->n_com > 0)
				mini->a_error = ft_execv(mini);
		}
		free_comand(mini);
		free_sections(mini);
		free(str);
	}
	return (mini->a_error);
}
