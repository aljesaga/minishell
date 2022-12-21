/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:25:37 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/21 09:48:46 by ioriola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_exe(char *gps, t_comand *com, t_mshell *mini)
{
	if (com->fd_out != STDOUT_FILENO)
		dup2(com->fd_out, STDOUT_FILENO);
	ft_close_fd(com->fd_in, mini);
	execve(gps, com->comand, mini->envs);
}

void	ft_run(t_comand *com, t_mshell *mini)
{
	char	*gps;
	int		i;

	if (com->fd_in != STDIN_FILENO)
		dup2(com->fd_in, STDIN_FILENO);
	if (!access(com->comand[0], X_OK))
		ft_exe(com->comand[0], com, mini);
	i = -1;
	while (mini->path != NULL && mini->path[++i])
	{
		gps = ft_strjoin(mini->path[i], com->comand[0]);
		if (!access(gps, X_OK))
			ft_exe(gps, com, mini);
		free(gps);
	}
	send_error(1, com->comand[0]);
	ft_close_fd(com->fd_in, mini);
	exit (127);
}

static void	init_childs(t_mshell *mini, t_comand *com, int i)
{	
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		mini->childs[i] = pid;
	else if (pid < 0)
		send_error(2, "fork");
	else
	{
		if (com->builtin == 1)
			exit(run_builtin(com, mini));
		else
			ft_run(com, mini);
	}
	if (com->wait == 1)
		waitpid(mini->childs[i], NULL, 0);
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
	while (++i < mini->n_com)
	{
		init_childs(mini, aux, i);
		aux = aux->next;
	}
	ft_reset_main_fd(mini);
	ft_free_fd(mini);
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
	status = 0;
	if (mini->n_com == 1 && !ft_strncmp(mini->comands->comand[0], "exit\0", 5))
		ft_exit(mini->comands, mini);
	else
	{
		mini->childs = ft_calloc(mini->n_com - 1, sizeof(pid_t *));
		if (!mini->childs)
			printf("children not found");
		status = built_or_exec(mini);
		free(mini->childs);
	}
	if (mini->envs != NULL)
		free_split(mini->envs);
	if (mini->path != NULL)
		free_split(mini->path);
	return (status);
}
