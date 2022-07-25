/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:56:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/25 13:30:36 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define MAGENTA "\033[1;35m"

# define RESET_C "\033[0m"

typedef struct s_env
{
	char			*value;
	int				change;
	struct s_env	*next;
}	t_env;

typedef struct s_mshell
{
	char	***command;
	int		fd_in;
	int		fd_out;
	int		n_env;
	int		l_exit;
	t_env	*env;
}	t_mshell;

/* env.c */

int		env_collec(char **env, t_mshell *mini);
void	new_env(char *str, int num, t_mshell *mini);
void	print_env(t_mshell *mini);

/* env_2_str.c */

char	**env_2_str(t_mshell *mini);

/* export.c */

void	shlvlup(t_mshell *mini);
int		export(char *str, t_mshell *mini);
void	unset(char *str, t_mshell *mini);

/* minishell.c */

int		main(int arc, char **arv, char **env);

/* read_line.c */

int		analyze_line(char *line, t_mshell *mini);

/*---------BASE_FTS--------*/

/* ft_cd.c */

int		ft_cd(char *str);

/* ft_echo.c */

int		ft_echo(char **str, t_mshell *mini);

	/*------PIPE------*/

#endif