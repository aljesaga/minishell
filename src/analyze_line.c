/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/18 18:31:36 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	free(mini->sections);
}

int	analyze_line(char *line, t_mshell *mini)
{
	t_section	*aux;

	if (!line || line[0] == '\0')
		return (0);
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
		aux = mini->sections;
		while (aux)
		{
			printf("-->%p----->%s---->%p\n\n\n\n", aux->str, aux->str, aux->next);
			aux = aux->next;
		}
		set_up_comand(mini);
		if (mini->n_com > 0)
			ft_execv(mini);
		free_sections(mini);
	}
	return (mini->a_error);
}
