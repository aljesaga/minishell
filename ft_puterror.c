/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:03:35 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/27 19:42:42 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterror(char *funtion, char *str)
{
	ft_putstr_fd("IA_minishell: ", STDOUT_FILENO);
	ft_putstr_fd(funtion, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putchar_fd('`', STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
}
