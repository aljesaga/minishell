/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:13:31 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/09 16:58:13 by alsanche         ###   ########lyon.fr   */
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
		if (aux->type == 6 || aux->type == 2)
			count++;
		aux = aux->next;
	}
	return (count);
}

void	add_part_comand(t_comand *new, t_mshell *mini, t_section *now, int args)
{
	t_section	*aux;
	int			i;

	aux = now->next;
	new->comand = ft_calloc(args + 2, sizeof(char *));
	new->builtin = now->builtin;
	new->fd_in = mini->fd_in;
	new->fd_out = STDOUT_FILENO;
	i = 0;
	new->comand[i] = now->str;
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
	mini->n_com = coms;
	mini->comands = ft_calloc(coms, sizeof(t_comand));
	coms = -1;
	while (aux != NULL && coms < mini->n_com)
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
			add_part_comand(&mini->comands[++coms], mini, aux, args);
		}
		aux = aux->next;
	}
}
