/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/03 17:06:00 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
t_mshell *g_mini; //quitar antes de entregar //

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

static void	set_and_exec(void)
{
	if (g_mini->a_error != 258)
	{
		set_up_comand();
		if (g_mini->n_com > 0)
			g_mini->a_error = ft_execv();
		ft_reset_main_fd();
	}
}

int	analyze_line(char *line)
{
	char		*str;

	if (line[0] == 34 && line[1] == 34 && line[2] == '\0')
	{
		ft_putstr_fd("IA_minishell: : command not found\n", 2);
		return (127);
	}
	if (!line || line[0] == '\0')
		return (0);
	g_mini->a_error = 0;
	if (check_quotes(line) == -1)
	{
		ft_putstr_fd("final quotes not found\n", 2);
		g_mini->a_error = 258;
	}
	if (g_mini->a_error != 258)
	{
		str = ft_strtrim(line, " ");
		ft_line_treatment(str);
		set_and_exec();
		free_comand();
		free_sections();
		free(str);
	}
	return (g_mini->a_error);
}
