/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:56:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/29 08:14:35 by ioriola          ###   ########.fr       */
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

/*---------BASE_FTS--------*/

	/* ft_cd.c */

int		ft_cd(char *line, t_mshell *mini);

	/* ft_echo.c */

int		ft_echo(char **str, t_mshell *mini);

	/* ft_pwd.c */

int		ft_pwd(void);

/*---------ENV--------*/

	/* env.c */

int		env_collec(char **env, t_mshell *mini);
void	new_env(char *str, int num, t_mshell *mini);
void	print_env(t_mshell *mini);

	/* env_2_str.c */

char	**env_2_str(t_mshell *mini);

	/* get_env_value.c */

char	*get_env_value(char *env_name, t_mshell *mini);

/* export.c */

void	export_sa(t_mshell *mini);
void	shlvlup(t_mshell *mini);
int		export(char *str, t_mshell *mini);
void	unset(char *str, t_mshell *mini);

/* minishell.c */

int		main(int arc, char **arv, char **env);

/* read_line.c */

int		analyze_line(char *line, t_mshell *mini);

/* ft_puterror.c */

void	ft_puterror(char *funtion, char *str);

	/*------PIPE------*/

#endif