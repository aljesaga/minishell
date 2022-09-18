/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:25:37 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/18 17:59:33 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_test(int fd, char *path, char **comand, char **enpv)
{
	dup2(fd, STDOUT_FILENO);
	execve(path, comand, enpv);
}

static void	ft_run(t_comand *com, t_mshell *mini)
{
	char	*gps;
	int		i;

	dup2(com->fd_in, STDIN_FILENO);
	close(com->fd_in);
	i = -1;
	if (!access(com->comand[0], X_OK))
		ft_test(com->fd_out, com->comand[0], com->comand, mini->envs);
	while (mini->path != NULL && mini->path[++i])
	{
		gps = ft_strjoin(mini->path[i], com->comand[0]);
		if (!access(gps, X_OK))
			ft_test(com->fd_out, gps, com->comand, mini->envs);
		free(gps);
	}
	send_error(1, com->comand[0]);
	close(com->fd_out);
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
		ft_run(com, mini);
	if (com->fd_in != 0)
		close (com->fd_in);
	if (com->fd_out != 1)
		close (com->fd_out);
	free(com->comand);
	com->builtin = 0;
	com->fd_in = 0;
	com->fd_out = 0;
}

void	ft_execv(t_mshell *mini)
{
	int	i;
	int	status;

	mini->envs = env_2_str(mini);
	mini->path = find_path(mini->envs);
	mini->childs = malloc(sizeof(pid_t *) * mini->n_com - mini->builts);
	if (!mini->childs)
		printf("children not found");
	i = -1;
	while (++i < mini->n_com)
	{
		if (mini->comands[i].builtin == 1)
			mini->l_exit = run_builtin(&mini->comands[i], mini);
		else
			init_childs(mini, &mini->comands[i], i);
	}
	i = -1;
	while (++i < mini->n_com)
		waitpid(mini->childs[i], &status, 0);
	if (WIFEXITED(status))
		mini->l_exit = WEXITSTATUS(status);
	free_split(mini->envs);
	free_split(mini->path);
	mini->fd_out = STDOUT_FILENO;
}
