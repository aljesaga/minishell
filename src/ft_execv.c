/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:25:37 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/30 18:43:37 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_run(t_comand *com, t_mshell *mini)
{
	char	*gps;
	int		i;

	if (com->fd_in != STDIN_FILENO)
		dup2(com->fd_in, STDIN_FILENO);
	if (!access(com->comand[0], X_OK))
	{
		dup2(com->fd_out, STDOUT_FILENO);
		close(com->fd_out);
		execve(com->comand[0], com->comand, mini->envs);
	}
	i = -1;
	while (mini->path != NULL && mini->path[++i])
	{
		gps = ft_strjoin(mini->path[i], com->comand[0]);
		if (!access(gps, X_OK))
		{
			 //printf("--->  %s\n", gps);
			dup2(com->fd_out, STDOUT_FILENO);
			if (com->fd_out != 1)
				close(com->fd_out);
			execve(gps, com->comand, mini->envs);
		}
		free(gps);
	}
	send_error(1, com->comand[0]);
	exit (127);
}

static void	init_childs(t_mshell *mini, t_comand *com, int i)
{	
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		mini->childs[i] = pid;
	else if (pid == -1)
		send_error(2, "fork");
	else
	{
		printf("---->%d--->%d---->%s\n", com->fd_in, com->fd_out, com->comand[0]);
		if (com->builtin == 1)
			mini->l_exit = run_builtin(com, mini);
		else
			ft_run(com, mini);
	}
	if (com->fd_in != 0)
		close(com->fd_in);
	if (com->fd_out != 1)
		close(com->fd_out);
}

static int	built_or_exec(t_mshell *mini)
{
	int			i;
	int			status;
	t_comand	*aux;

	aux = mini->comands;
	i = -1;
	while (++i < mini->n_com && aux)
	{
		init_childs(mini, aux, i);
		aux = aux->next;
	}
	i = -1;
	while (++i < mini->n_com)
		waitpid(mini->childs[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	ft_execv(t_mshell *mini)
{
	int	status;

	mini->envs = env_2_str(mini);
	mini->path = find_path(mini->envs);
	mini->childs = malloc(sizeof(pid_t *) * mini->n_com);
	if (!mini->childs)
		printf("children not found");
	else{
		status = built_or_exec(mini);
		free(mini->childs);
		free_split(mini->envs);
		free_split(mini->path);
		mini->fd_in = STDIN_FILENO;
	}
	return (0);
}
