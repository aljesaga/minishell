/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:04:13 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/25 11:16:35 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
El comando cd
Este sencillo comando, lo que nos va a permitir es cambiar nuestro directorio de trabajo (o directorio
actual). Es una abreviatura (como muchos otros comandos) de lo que hace, en este caso de Change
Directory. Podemos necesitar cambiar nuestro directorio de trabajo si vamos a trabajar con muchos
archivos que estén en el direcotrio al que nos cambiamos, y no queremos teclear siempres su ruta
completa por resultar esto demasiado incómodo y largo. Partimos de /home/usuario, y nos quere-
mos cambiar a /usr/local, que es donde residen muchas cosas personalizadas de nuestro sistema.

Se podría hacer de la siguiente forma:
[usuario@maquina usuario]$ cd /usr/local/

Y entonces ya estaríamos en /usr/local:
[usuario@maquina local]$

Si simplemente escribimos cd, sin ningún argumento (dato que necesita un comando para operar
de una manera u otra, con un archivo u otro... como después veremos), lo que hará será llevarnos a
nuestro directorio personal:

[usuario@maquina local]$ cd
[usuario@maquina usuario]$

Como puedes ver, ahora nuestro directorio de trabajo es /home/usuario, que es nuestro directorio
personal.

Pero hay algunas cosas que no hemos contado de las referencias relativas. Es que dos puntos seguidos
.. se refieren al directorio inmediatamente anterior (superior) al que nos encontramos, y un punto .
se refiere al directorio en el que nos encontramos (directorio actual). Si estando en /home/usuario
escribes cd ., te darás cuenta de que no cambia de directorio, se queda en el actual, de la misma
manera que si hubieras hecho cd .. te habría llevado a /home , el directorio inmediatamente supe-
rior. Estos dos comandos equivaldrían a cd ./ y cd ../; es lo mismo, pero es realente con la barra
como deben utilizarse estos comandos (puesto que nos estamos refiriendo a directorios). Utilizarlos
sin ella, puede dar lugar a confusión y equivocaciones (recuerda que los archivos y directorios ocultos
comienzan su nombre por .). Ahora ya sabes que para poder ir a /home/usuario/documentos
podríamos haber hecho:

$ cd ./documentos

Lo cual no es muy eficiente en este caso, pero como veremos más adelante, es de obligada utilización
para ejecutar un comando en el directorio actual si este directorio actual no está en la PATH. Por
ejemplo para ejecutar un programa (como veremos más adelante) que estuviese en /home/usuario,
al no estar esta ruta en $PATH, necesitaríamos hacerlo así (estando en /home/usuario):

$ ./miprograma

Te habrás dado cuenta de que con una referencia relativa es más cómodo, más sencillo y más rápido.
Si simplemente dijésemos desde /home/usuario miprograma a BASH, no lo encontraría, y nos
devolvería que no ha encontrado el comando. ¿Por qué? Pues es fácil, /home/usuario, que es donde
reside miprograma, no está en $PATH. Bueno, la ejecución para después, ahora sigamos:
Desde /home/usuario podríamos haber ido a /usr/local con una referencia relativa también:

[usuario@maquina usuario]$ cd ../../usr/local

Este comando sube dos niveles (al directorio inmediatamente superior a /home/usuario, que es
/home, y luego al directorio inmediatamente superior a /home que es /; una ez allí busca mediate
referencia relativa a / el directorio usr, y una vez dentro, mediante una referencia relativa al directorio
usr, busca el directorio local. En este caso es más rápido introducir cd /usr/local que usar
una referencia relativa al directorio actual. Generalmente, usaremos referencias absolutas (al sistema
de archivos, /) cuando lo que queremos buscar (en este caso un directorio) se encuentre varios niveles
por encima del directorio actual, o en una ruta distinta como en este ejemplo.
*/


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
