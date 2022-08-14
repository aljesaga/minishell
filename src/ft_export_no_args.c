/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:52:50 by ioriola           #+#    #+#             */
/*   Updated: 2022/08/14 14:34:19 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_export_no_args(t_mshell *mini)
{
	char	**export;
	char	*aux;
	int		y;
	int		x;

	export = env_2_str(mini);
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
	y = -1;
	while (export[++y])
		if (export[y][0] != '\0')
			printf("declare -x %s\n", export[y]);
	free_split(export);
}
