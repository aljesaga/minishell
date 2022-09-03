/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_segtion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:35:08 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/03 19:48:47 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	else if (!ft_strncmp(str, ">>", 2))
		return (4);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (3);
	else if (!ft_strncmp(str, "|", 1))
		return (5);
	else
		return (6);
}

/*char	*clean(char *str)
{
	char	*aux;
	int		quotes;
	int		i;

	aux = malloc(sizeof(char) * (ft_strlen(str) + 1));
	quotes = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == 39 && quotes == 0)
			quotes = 1;
		else if (str[i] == 39 && quotes == 1)
			quotes = 0;
		else if (str[i] == 34 && quotes == 0)
			quotes = 2;
		else if (str[i] == 34 && quotes == 2)
			quotes = 0;
		else
			aux[i] == str[i];
	}
	aux[i] = '\0';
	return (aux);
}

char	*clean_expand(char *str)
{
	char	*aux;
	char	*end;

	aux = str_expand(str);
	end = clean(aux);
	free(aux);
	return (end);
}*/

void	add_segtion(char *str, t_mshell *mini, int check)
{
	t_section	*new;
	t_section	*aux;

	new = malloc(sizeof(t_section));
	if (!new)
		printf("Memory Error");
	new->str = ft_strdup(str);
	new->type = ft_type(str);
	new->next = NULL;
	if (check == 0)
		mini->sections = new;
	else
	{
		aux = mini->sections;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}
