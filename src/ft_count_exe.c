/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:13:31 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/22 16:57:35 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:48:26 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/09 12:49:37 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_com(t_mshell *mini)
{
	int			count;
	t_section	*aux;

	count = 0;
	aux = mini->sections;
	while (aux)
	{
		if (aux->type == 6)
			count++;
		aux = aux->next;
	}
	return (count);
}

t_section	*add_part(t_comand *new, t_mshell *mini, t_section *now, int args)
{
	t_section	*aux;
	int			i;

	aux = now->next;
	new->comand = malloc(sizeof(char *) * args + 2);
	new->builtin = now->builtin;
	new->fd_in = mini->fd_in;
	new->fd_out = STDOUT_FILENO;
	i = 0;
	new->comand[i] = now->str;
	while (aux != NULL && ++i < args)
	{
		new->comand[i] = aux->str;
		aux = aux->next;
	}
	while (aux)
	{
		if (aux->type == 1 || aux->type == 2
			|| aux->type == 3 || aux->type == 4 || aux->type == 5)
			check_fd(mini, new, aux);
		if (aux->type == 5)
			break ;
		aux = aux->next;
	}
	return (aux);
}

t_section	*add_comand(t_mshell *mini, t_section *aux, int coms)
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
	temp = add_part(&mini->comands[coms], mini, aux, args);
	return (temp);
}

void	set_up_comand(t_mshell *mini)
{
	t_section	*aux;
	int			coms;

	aux = mini->sections;
	mini->n_com = count_com(mini);
	mini->comands = malloc(sizeof(t_comand) * mini->n_com + 1);
	coms = -1;
	while (aux && coms < mini->n_com)
	{
		if (aux->type != 6)
		{
			not_comand(mini, aux);
			aux = aux->next;
		}
		else if (aux->type == 6 && coms < mini->n_com)
			aux = add_comand(mini, aux, ++coms);
	}
}
