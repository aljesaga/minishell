/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:05:03 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/19 14:55:29 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i-- > 0)
		free(str[i]);
	free(str);
}
