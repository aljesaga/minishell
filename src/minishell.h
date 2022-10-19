/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:56:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/10/19 18:51:07 by alsanche         ###   ########lyon.fr   */
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
	int					builtin;
	int					here_expand;
	struct s_section	*next;
}	t_section;

typedef struct s_comand
{
	char			**comand;
	int				builtin;
	int				n_comand;
	int				n_arg;
	int				fd_in;
	int				fd_out;
	int				wait;
	struct s_comand	*next;
}	t_comand;

typedef struct s_mshell
{
	int			fd_in;
	int			n_com;
	int			n_env;
	int			fd_out;
	int			builts;
	int			quotes;
	int			**pipex;
	int			a_error;
	int			l_exit;
	char		**path;
	char		**envs;
	t_env		*env;
	pid_t		*childs;
	t_comand	*comands;
	t_section	*sections;
}	t_mshell;

// add_segtion.c //
void		add_segtion(char *str, t_mshell *mini, int check);

// analyze_line.c //
void		free_comand(t_mshell *mini);
void		free_sections(t_mshell *mini);
int			analyze_line(char *line, t_mshell *mini);

// builtin.c //
int			is_builtin(char *str);
int			run_builtin(t_comand *com, t_mshell *mini);

// close_fd.c //
void		ft_reset_main_fd(t_mshell *mini);
void		ft_close_fd(int fd_in, t_mshell *mini);
void		ft_free_fd(t_mshell *mini);

// ft_set_fd.c //
int			*build_tunnel(t_comand *com, t_mshell *mini);
void		check_fd(t_mshell *mini, t_comand *new, t_section *now);
void		not_comand(t_mshell *mini, t_section *now);

// env_2_str.c //
char		**find_path(char **enpv);
char		**env_2_str(t_mshell *mini);

// exit.c //
void		ft_exit(t_comand *com, t_mshell *mini);

// ft_cd.c //
int			ft_cd(char *line, t_mshell *mini);

//ft_count_exe.c //
t_section	*add_part(t_comand *new, t_mshell *mini, t_section *now);
t_section	*add_comand(t_mshell *mini, t_section *aux, t_comand *new);
void		set_up_comand(t_mshell *mini);

// ft_echo.c //
int			ft_echo(t_comand *com);

// ft_env.c //
int			env_collec(char **env, t_mshell *mini);
void		new_env(char *str, int num, t_mshell *mini);
int			ft_env(t_comand *com, t_mshell *mini);

// ft_execv.c //
int			ft_execv(t_mshell *mini);

// ft_expand.c //
int			check_name(t_mshell *mini, char *str);
char		*str_expand(char *str, t_mshell *mini);

// ft_export_no_args.c //
int			ft_export_no_args(t_comand *com, t_mshell *mini);

// ft_export.c //
int			ft_export(char **comand, t_mshell *mini);

// ft_here_doc.c //
int			ft_here_doc(t_mshell *mini, char *arv, int check);

// ft_puterror.c //
void		send_error(int n, char *str);
void		ft_puterror(char *funtion, char *str);

// ft_pwd.c //
int			ft_pwd(t_comand *com);

// ft_type.c //
void		assign_type(t_mshell *mini);

// ft_unset.c //
void		unset_mini(t_mshell *mini);
int			ft_unset(char *str, t_mshell *mini);

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
