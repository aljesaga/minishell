/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:56:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/31 17:53:59 by ioriola          ###   ########.fr       */
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
# include <libft.h>

# define RESET			"\033[0m"
# define BG				"\033[40m"
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define PURPLE			"\033[0;35m"
# define CYAN			"\033[0;36m"
# define WHITE			"\033[0;37m"
# define GRAY			"\033[1;30m"
# define LIGHTRED		"\033[1;31m"
# define LIGHTGREEN		"\033[1;32m"
# define LIGHTYELLOW	"\033[1;33m"
# define LIGHTBLUE		"\033[1;34m"
# define LIGHTPURPLE	"\033[1;35m"
# define LIGHTCYAN		"\033[1;36m"
# define LIGHTWHITE		"\033[1;37m"

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

// analyze_line.c //
int			analyze_line(char *line, t_mshell *mini);

// builtin.c //
int		is_builtin(char *str);
void	run_builtin(char **args, char *line, t_mshell *mini);

// env_2_str.c //
char		**env_2_str(t_mshell *mini);

// ft_cd.c //
int			ft_cd(char *line, t_mshell *mini);

// ft_echo.c //
int			ft_echo(char **str, t_mshell *mini);

// ft_env.c //
int			env_collec(char **env, t_mshell *mini);
void		new_env(char *str, int num, t_mshell *mini);
void		ft_env(t_mshell *mini);

// ft_export_no_args.c //
void		ft_export_no_args(t_mshell *mini);

// ft_export.c //
int			ft_export(char *str, t_mshell *mini);

// ft_puterror.c //
void		ft_puterror(char *funtion, char *str);

// ft_pwd.c //
int			ft_pwd(t_mshell *mini);

// ft_unset.c //
void		ft_unset(char *str, t_mshell *mini);

// get_env_value.c //
char		*get_env_value(char *env_name, t_mshell *mini);

// init_mini.c //
t_mshell	*init_mini(char **env);

// minishell.c //
int			main(int arc, char **arv, char **env);

// shlvlup.c //
void		shlvlup(t_mshell *mini);

#endif
