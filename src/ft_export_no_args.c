/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:52:50 by ioriola           #+#    #+#             */
/*   Updated: 2023/01/19 17:01:07 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	export_print(t_comand *com, char **env)
{
	int		y;
	int		x;
	int		ck;

	y = -1;
	while (env[++y])
	{
		ck = 0;
		if (env[y][0] != '\0')
		{
			dprintf(com->fd_out, "declare -x ");
			x = -1;
			while (env[y][++x] != '\0')
			{
				ft_putchar_fd(env[y][x], com->fd_out);
				if (env[y][x] == '=' || (env[y][x + 1] == '\0' && ck == 1))
				{
					ck = 1;
					ft_putchar_fd('"', com->fd_out);
				}
			}
			ft_putchar_fd('\n', com->fd_out);
		}
	}
}

int	ft_export_no_args(t_comand *com)
{
	char	**export;
	char	*aux;
	int		y;
	int		x;

	export = env_2_str();
	if (!export)
		return (1);
	y = -1;
	while (export[++y])
	{
		x = y;
		while (export[++x])
		{
			if (ft_strcmp(export[y], export[x]) > 0)
			{
				aux = export[y];
				export[y] = export[x];
				export[x] = aux;
			}
		}
	}
	export_print(com, export);
	free_split(export);
	return (0);
}
