/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/24 18:29:34 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	analyze_line(char *line, t_mshell *mini)
{
	t_section	*aux;

	if (!line)
		return (0);
	ft_line_treatment(line, mini);
	/*mini->fd_out = STDOUT_FILENO;
	if (is_builtin(args[0]))
		run_builtin(args, line, mini);
	else
		run_binary(); << Todavía no existe. */
	aux = mini->sections;
	while (aux->next)
	{
		printf("str--->%s\n", mini->sections->str);
		printf("type-->%d\n", mini->sections->type);
		printf("*****************\n");
		aux = aux->next;
	}
	return (0);
}
