/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:13:31 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/07 17:29:48 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_take_msn(char *std, t_mshell *mini)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(std);
	close (mini->fd_out);
	while (1)
	{
		ft_putstr_fd("IA_minishell->heredoc> ", 1);
		temp = get_next_line(STDIN_FILENO);
		if (!temp)
		{
			close (mini->fd_in);
			exit (1);
		}
		if (!ft_strncmp(temp, std, len) && temp[len] == '\n')
		{
			close (mini->fd_in);
			free(temp);
			exit (0);
		}
		ft_putstr_fd(temp, mini->fd_in);
		free(temp);
	}
}

static int	ft_here_doc(t_mshell *mini, char *arv)
{	
	int		here[2];
	pid_t	child;

	pipe(here);
	child = fork();
	if (child < 0 || here[FD_R] < 0)
		ft_putstr_fd("here_doc failed", 1);
	mini->fd_in = here[FD_W];
	mini->fd_out = here[FD_R];
	if (child == 0)
	{
		ft_take_msn(arv, mini);
	}
	else
	{
		waitpid(child, NULL, 0);
		close(here[FD_W]);
		return (here[FD_R]);
	}
}

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
	i = 0;
	new->comand[i] = new->str;
	while (++i < args)
	{
		new->comand[i] = aux->str;
		aux = aux->next;
	}
	while (aux)
	{
		if (aux->type == 2)
			new->fd_in = here_doc(mini, aux->next->str);
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
