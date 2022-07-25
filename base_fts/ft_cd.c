/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:04:13 by alsanche          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/25 11:36:44 by ioriola          ###   ########.fr       */
=======
/*   Updated: 2022/07/19 12:43:10 by alsanche         ###   ########lyon.fr   */
>>>>>>> 38e54f891ccb789c798909cd51c900f3cd4e0f0d
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
/*
cd ruta_absoluta
cd [sin_argumentos] lleva a HOME
~?????

cd .. directorio inmediatamente anterior (superior) = cd ../
cd . directorio en el que nos encontramos (directorio actual) = cd ./

*/

=======
>>>>>>> 38e54f891ccb789c798909cd51c900f3cd4e0f0d
int	ft_cd(char *str)
{
	if (str[0] == '\0')
		write(1, "/home/mi_usuario\n", 18);
	else if (str[0] == '.' && str[1] == '.')
	{
		if (str[2] == '/')
			write(1, "/anterior/carpeta_en_ruta_anterior\n", 36);
		else
			write(1, "/ahora_aqui/actual\n", 20);
	}
	else if (str)
	{
		write(1, "/actual/", 9);
		printf("%s\n", str);
	}
	else
		write(1, "ERROR\n", 6);
	return (0);
}
