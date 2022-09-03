/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:56:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/09/03 19:47:35 by alsanche         ###   ########lyon.fr   */
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
# include "../lib/libft/libft.h"

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
# define FD_R			0
# define FD_W			1

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_section
{
	char				*str;
	int					type;
	struct s_section	*next;
}	t_section;

typedef struct s_mshell
{
	int			fd_in;
	int			n_com;
	int			n_env;
	int			fd_out;
	int			quotes;
	int			l_exit;
	char		**path;
	t_env		*env;
	pid_t		*childs;
	t_section	*sections;
}	t_mshell;

// add_segtion.c //
void		add_segtion(char *str, t_mshell *mini, int check);

// analyze_line.c //
int			analyze_line(char *line, t_mshell *mini);

// builtin.c //
int			is_builtin(char *str);
void		run_builtin(char **args, char *line, t_mshell *mini);

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

// ft_execv.c //
void		ft_execv(t_mshell *mini, char **arv, int x);

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

//  line_treatment.c //
int			word_width(char *str, t_mshell *mini);
int			check_quotes(char *line, t_mshell *mini);
void		ft_line_treatment(char *line, t_mshell *mini);

// minishell.c //
int			main(int arc, char **arv, char **env);

// shlvlup.c //
void		shlvlup(t_mshell *mini);
char		**ft_split_ignore(char const *s, char c);

#endif
