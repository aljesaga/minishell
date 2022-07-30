/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:52:50 by ioriola           #+#    #+#             */
/*   Updated: 2022/07/30 16:53:07 by ioriola          ###   ########.fr       */
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
		printf("---->%s\n", export[y]);
	free_split(export);
}