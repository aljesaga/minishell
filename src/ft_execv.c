/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:25:37 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/07 11:46:27 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_test(int fd, char *path, char **comand, char **enpv)
{
	dup2(fd, STDOUT_FILENO);
	execve(path, comand, enpv);
}

static void	ft_run(int *fd, char **comand, t_mshell *mini)
{
	char	*gps;
	int		i;

	close(fd[FD_R]);
	dup2(mini->fd_in, STDIN_FILENO);
	close(mini->fd_in);
	i = -1;
	if (!access(comand[0], X_OK))
		ft_test(mini->fd_out, comand[0], comand, env_2_str(mini->env));
	while (mini->path != NULL && mini->path[++i])
	{
		gps = ft_strjoin(mini->path[i], comand[0]);
		if (!access(gps, X_OK))
			ft_test(mini->fd_out, gps, comand, env_2_str(mini->env));
		free(gps);
	}
	if (mini->path == NULL)
		send_error(3, comand[0]);
	else
		send_error(1, comand[0]);
	close(fd[FD_W]);
	exit (127);
}

static void	init_childs(t_mshell *mini, char **cmd, int i)
{	
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid != 0)
		mini->childs[i] = pid;
	else if (pid == -1)
		send_error(2, "fork");
	else
	{
		if (i + 1 == mini->n_com)
			selec_out_file(mini, mini->file_out);
		else
			mini->fd_out = fd[FD_W];
		ft_run(fd, cmd, mini);
	}
	close(fd[FD_W]);
	close(mini->fd_in);
	mini->fd_in = fd[FD_R];
}

void	ft_execv(t_mshell *mini)
{
	int	i;
	int	status;

	mini->path = find_path(mini->env);
	draw_command(mini, arv, x);
	mini->childs = malloc(sizeof(pid_t *) * mini->n_com);
	if (!mini->childs)
		send_error(0, "children not found");
	i = -1;
	while (++i < mini->n_com)
		init_childs(mini, mini->command[i], i);
	i = -1;
	while (++i < mini->n_com)
		waitpid(mini->childs[i], &status, 0);
	if (WIFEXITED(status))
		mini->l_exit = WEXITSTATUS(status);
}
