/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:29:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/08/24 19:00:29 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	analyze_line(char *line, t_mshell *mini)
{
	char	**args;
	char	*str;
	int		i;

	if (!line)
		return (0);
	str = line;
	if (check_quotes(line, mini) == 1)
		printf("final quotes not found");
	args = ft_split(line, ' ');
	mini->fd_out = STDOUT_FILENO;
	if (is_builtin(args[0]))
		run_builtin(args, line, mini);
	/*else
		run_binary(); << Todavía no existe. */
	i = -1;
	while (args[++i] != NULL)
		printf("---args--%d----%s\n", i, args[i]);
	free_split(args);
	return (0);
}
