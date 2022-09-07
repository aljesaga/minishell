/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/07 11:15:19 by alsanche         ###   ########lyon.fr   */
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

int	analyze_line(char *line, t_mshell *mini)
{
	char		*str;
	t_section	*aux;

	if (!line)
		return (0);
	str = line;
	if (check_quotes(line, mini) == 1)
		printf("final quotes not found");
	ft_line_treatment(line, mini);
	mini->fd_out = STDOUT_FILENO;
	aux = mini->sections;
	ft_count_exe(mini);
	free_sections(mini);
	return (0);
}
