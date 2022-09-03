/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba_segmentar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 11:41:48 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/03 14:34:37 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c2;
	unsigned char	*c1;

	i = 0;
	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	while (*c1 != '\0' && *c2 != '\0' && i < n)
	{
		if ((*c1 <= 0 || *c1 == 127) || (*c2 <= 0 || *c2 >= 127))
			return ('\0');
		if (*c1 != *c2)
			return (*c1 - *c2);
		i++;
		c1++;
		c2++;
	}
	if (i != n)
	{
		return (*c1 - *c2);
	}
	return (0);
}

static int	word_width(const char *str)
{
	int	count;

	count = 0;
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	else if (!ft_strncmp(str, ">>", 2))
		return (2);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	else if (!ft_strncmp(str, "|", 1))
		return (1);
	while (str[count] != '\0')
	{
		if (str[count] == ' ' || str[count] == '|')
			break ;
		else if (str[count] == '<' || str[count] == '>')
		{
			if (str[count + 1] != '<' && str[count + 1] != '>')
				++count;
			break ;
		}
		count++;
	}
	return (count);
}

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

int	check_quotes(char *line)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (line[++i] != '\0')
	{
		if (line[i] == 39 && quotes == 0)
			quotes = 1;
		else if (line[i] == 39 && quotes == 1)
		{
			quotes = 0;
			return (i);
		}
		else if (line[i] == 34 && quotes == 0)
			quotes = 2;
		else if (line[i] == 34 && quotes == 2)
		{
			quotes = 0;
			return (i);
		}
	}
	if (quotes == 2 || quotes == 1)
		return (-1);
	return (0);
}

static int	ft_type(char *line)
{
	if (!ft_strncmp(line, "<<", 2))
		return (2);
	else if (!ft_strncmp(line, ">>", 2))
		return (4);
	else if (!ft_strncmp(line, "<", 1))
		return (1);
	else if (!ft_strncmp(line, ">", 1))
		return (3);
	else if (!ft_strncmp(line, "|", 1))
		return (5);
	else
		return (6);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) < len)
		len = ft_strlen(s);
	new = (char *)malloc(sizeof(*s) * (len + 1));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = s[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	ft_line_treatment(char *line)
{
	size_t	j;
	char	*aux;
	int		limit;

	j = 0;
	limit = 0;
	if (check_quotes(line) == -1)
	{
		printf("OPEN QUOTES");
		exit(1);
	}
	while (line[j] != '\0')
	{
		if (line[j] == 34 || line[j] == 39)
			limit = check_quotes(&line[j]) + 1;
		else
			limit = word_width(&line[j]);
		aux = ft_substr(line, j, limit);
		printf("%s----->type=%d\n", aux, ft_type(aux));
		free(aux);
		j += limit;
		if (line[j] == ' ')
			j++;
	}
}

int	main(int arc, char **line)
{
	(void)arc;
	ft_line_treatment(line[1]);
	return (0);
}
