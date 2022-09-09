/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:13:31 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/09 12:23:04 by alsanche         ###   ########lyon.fr   */
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

static t_comand	*add_part_comand(t_mshell *mini, t_section *now, int args)
{
	t_section	*aux;
	t_comand	*new;
	int			i;

	aux = now->next;
	new = malloc(sizeof(t_comand));
	new->comand = ft_calloc(args + 2, sizeof(char *));
	new->builtin = now->builtin;
	new->fd_in = mini->fd_in;
	new->fd_out = STDOUT_FILENO;
	i = 0;
	new->comand[i] = new->str;
	while (++i < args)
	{
		new->comand[i] = aux->str;
		aux = aux->next;
	}
	while (aux)
	{
		if (aux->type == 1 || aux->type == 2
			|| aux->type == 3 || aux->type == 4)
			check_fd(mini, new, aux);
		else if (aux->type == 5)
			build_tunnel(mini, new);
		if (aux->type == 3 || aux->type == 4 || aux->type == 5)
			break ;
		aux = aux->next;
	}
}

void	set_up_comand(t_mshell *mini)
{
	t_section	*aux;
	t_section	*temp;
	int			args;
	int			coms;

	aux = mini->sections;
	coms = count_com(mini);
	mini->comands = ft_calloc(coms, sizeof(t_comand));
	coms = -1;
	while (aux != NULL)
	{
		args = 0;
		if (aux->type == 6)
		{
			temp = aux->next;
			while (temp && temp->type == 7)
			{
				args++;
				temp = temp->next;
			}
			mini->comands[++coms] = add_part_comand(mini, aux, args);
		}
		aux = aux->next;
	}
}
