/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:14:14 by alsanche          #+#    #+#             */
/*   Updated: 2021/09/26 13:14:18 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

size_t	ft_len(const char *c);
char	*get_next_line(int fd);
char	*ft_join(char const *s1, char const *s2, size_t c);
char	*ft_strup(char *s1, size_t i);
char	*ft_remove(char *str, size_t i);
size_t	ft_check(char *str);
#endif
