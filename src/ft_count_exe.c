/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:13:31 by alsanche          #+#    #+#             */
/*   Updated: 2023/01/18 17:01:10 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_com(void)
{
	int			count;
	t_section	*aux;

	count = 0;
	aux = g_mini->sections;
	while (aux)
	{
		if (aux->type == 6)
			count++;
		aux = aux->next;
	}
	return (count);
}

t_section	*add_part(t_comand *new, t_section *now)
{
	t_section	*aux;
	int			i;

	aux = now;
	new->comand = ft_calloc(new->n_arg + 1, sizeof(char *));
	new->builtin = now->builtin;
	new->fd_in = g_mini->fd_in;
	new->fd_out = g_mini->fd_out;
	i = -1;
	while (aux && aux->str != NULL && ++i < new->n_arg)
	{
		new->comand[i] = ft_strdup(aux->str);
		aux = aux->next;
	}
	while (aux)
	{
		if (aux->type == 1 || aux->type == 2 || aux->type == 8
			|| aux->type == 3 || aux->type == 4 || aux->type == 5)
			check_fd(new, aux);
		if (aux->type == 5 || aux->type == 8)
			break ;
		aux = aux->next;
	}
	return (aux);
}

t_section	*add_comand(t_section *aux, t_comand *new)
{
	t_section	*temp;
	int			args;

	if (aux->next)
		temp = aux->next;
	else
		temp = NULL;
	args = 0;
	while (temp && temp->type == 7)
	{
		args++;
		temp = temp->next;
	}
	new->n_arg = args + 1;
	temp = add_part(new, aux);
	return (temp);
}

static t_comand	*create_add(int coms)
{
	t_comand	*new;
	t_comand	*aux;

	new = ft_calloc(1, sizeof(t_comand));
	new->n_comand = coms;
	if (coms == 0)
		g_mini->comands = new;
	else
	{
		aux = g_mini->comands;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
	return (new);
}

void	set_up_comand(void)
{
	t_section	*aux;
	t_comand	*new;
	int			coms;

	aux = g_mini->sections;
	g_mini->n_com = count_com();
	coms = -1;
	while (aux && coms < g_mini->n_com)
	{
		if (aux->type != 6)
		{
			mini_check_fd(aux);
			aux = aux->next;
		}
		else if (aux->type == 6 && coms < g_mini->n_com)
		{
			new = create_add(++coms);
			aux = add_comand(aux, new);
		}
	}
}
