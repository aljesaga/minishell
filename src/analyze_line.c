/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/10 16:53:47 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_line	*line_data(char **arv)
{
	int		i;
	t_line	data;

	i = -1;
	data = malloc(sizeof(t_line));
	data.n_cmd = 0;
	data.n_in = 0;
	data.n_out = 0;
	data.n_pipe = 0;
	while (arv[++i])
	{
		if (arv[i][0] == '<')
			data.n_in++;
		else if (arv[i][0] == '>')
			data.n_out++;
		else if (arv[i][0] == '|')
			data.n_pipe++;
		else
			data.n_cmd++;
	}
}

int	analyze_line(char *line, t_mshell *mini)
{
	char	**args;
	t_line	*data;

	if (!line)
		return (0);
	args = ft_split(line, ' ');
	data = line_data(arv);
	mini->fd_out = STDOUT_FILENO;
	if (is_builtin(args[0]))
		run_builtin(args, line, mini);
	else
	//	run_binary(); << Todavía no existe. 
	free_split(args);
	return (0);
}
