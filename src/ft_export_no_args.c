/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:52:50 by ioriola           #+#    #+#             */
/*   Updated: 2022/12/28 13:51:25 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	export_print(t_comand *com, char **export)
{
	int		y;
	int		x;

	y = -1;
	while (export[++y])
	{
		if (export[y][0] != '\0')
		{
			dprintf(com->fd_out, "declare -x ");
			x = -1;
			while (export[y][++x] != '\0')
			{
				ft_putchar_fd(export[y][x], com->fd_out);
				if (export[y][x] == '=' || export[y][x + 1] == '\0')
					ft_putchar_fd('"', com->fd_out);
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
