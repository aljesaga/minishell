/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:06:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/24 18:23:25 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_put(char *temp, t_mshell *mini, int check, int *here)
{
	char	*aux;

	if (check == 0)
	{
		aux = temp;
		temp = str_expand(aux, mini);
		free(aux);
	}
	ft_putstr_fd(temp, here[FD_W]);
	ft_putchar_fd('\n', here[FD_W]);
	free(temp);
}

static void	ft_take_msn(char *std, t_mshell *mini, int check, int *here)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(std);
	close(here[FD_R]);
	while (1)
	{
		temp = readline("-> ");
		if (!temp)
		{
			close (here[FD_W]);
			exit (1);
		}
		if (!ft_strncmp(temp, std, len))
		{
			close (here[FD_W]);
			free(temp);
			exit (0);
		}
		check_put(temp, mini, check, here);
	}
}

int	ft_here_doc(t_mshell *mini, char *arv, int check)
{	
	int		here[2];
	pid_t	child;
	int		status;

	pipe(here);
	child = fork();
	if (child < 0)
		ft_putstr_fd("here_doc failed", 1);
	else if (child == 0)
	{
		ft_take_msn(arv, mini, check, here);
	}
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		mini->l_exit = WEXITSTATUS(status);
	close(here[FD_W]);
	return (here[FD_R]);
}
