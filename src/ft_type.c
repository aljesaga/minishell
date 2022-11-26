/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:09:40 by alsanche          #+#    #+#             */
/*   Updated: 2022/11/26 19:30:28 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	its_comand(t_mshell *mini, int check)
{
	t_section	*aux;
	int			prev;
	int			i;

	prev = 0;
	i = -1;
	aux = mini->sections;
	while (++i < check - 2)
	{
		if (aux->type == 6)
			prev = 1;
		if (aux->type == 5 || aux->type == 8)
			prev = 0;
		aux = aux->next;
	}
	if (prev == 1)
		return (0);
	if ((aux->type >= 1 && aux->type <= 4) && aux->next->type == 7)
		return (1);
	return (0);
}

static void	type_plus(t_section *atl, t_mshell *mini, int check)
{
	t_section	*aux;
	int			i;

	if (check == 0)
	{
		atl->type = 6;
		atl->builtin = is_builtin(atl->str);
	}
	else
	{
		i = check;
		aux = mini->sections;
		while (--check > 0)
			aux = aux->next;
		if (aux->type == 5 || aux->type == 8 || its_comand(mini, i) == 1)
		{
			atl->type = 6;
			atl->builtin = is_builtin(atl->str);
			mini->builts += atl->builtin;
		}
		else
			atl->type = 7;
	}
}

static void	ft_type(t_section *atl, t_mshell *mini, int check)
{
	atl->builtin = 0;
	if (!ft_strncmp(atl->str, "<<", 2))
		atl->type = 2;
	else if (!ft_strncmp(atl->str, ">>", 2))
		atl->type = 4;
	else if (!ft_strncmp(atl->str, "<", 1))
		atl->type = 1;
	else if (!ft_strncmp(atl->str, ">", 1))
		atl->type = 3;
	else if (!ft_strncmp(atl->str, "|", 1))
		atl->type = 5;
	else if (!ft_strncmp(atl->str, ";", 1))
		atl->type = 8;
	else
		type_plus(atl, mini, check);
}

void	assign_type(t_mshell *mini)
{
	int			i;
	t_section	*aux;

	i = 0;
	aux = mini->sections;
	while (aux)
	{
		ft_type(aux, mini, i);
		i++;
		if ((aux->type == 1 || aux->type == 2 || aux->type == 3
				|| aux->type == 4) && (aux->next == NULL))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			mini->a_error = 258;
		}
		if ((aux->type == 5 || aux->type == 8)
			&& (aux->next->str[0] == ';' || aux->next->str[0] == '|'))
		{
			printf("syntax error near unexpected token `%s'\n", aux->next->str);
			mini->a_error = 258;
			break ;
		}
		aux = aux->next;
	}
}
