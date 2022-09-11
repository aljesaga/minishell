/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/11 16:16:45 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_sections(t_mshell *mini)
{
	t_section	*aux;

	while (mini->sections != NULL)
	{
		aux = mini->sections->next;
		free(mini->sections->str);
		free(mini->sections);
		mini->sections = aux;
	}
	mini->sections = NULL;
}

void	free_comand(t_mshell *mini)
{
	int	i;

	i = mini->n_com;
	while (--i > -1)
	{
		free_split(mini->comands[i].comand);
	}
	free(mini->comands);
}

int	analyze_line(char *line, t_mshell *mini)
{
	char		*str;

	if (!line)
		return (0);
	str = line;
	mini->a_error = 0;
	if (check_quotes(line, mini) == 1)
	{
		printf("final quotes not found");
		return (258);
	}
	ft_line_treatment(line, mini);
	if (mini->a_error != 258)
	{
		mini->fd_in = STDIN_FILENO;
		mini->fd_out = STDOUT_FILENO;
		set_up_comand(mini);
		if (mini->n_com > 0)
			ft_execv(mini);
		//free_comand(mini);
		free_sections(mini);
	}
	return (mini->a_error);
}
