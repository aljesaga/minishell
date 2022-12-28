/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:56:28 by alsanche          #+#    #+#             */
/*   Updated: 2022/12/28 14:02:23 by alsanche         ###   ########lyon.fr   */
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
# define LRED			"\033[1;31m"
# define LGREEN			"\033[1;32m"
# define LYELLOW		"\033[1;33m"
# define LBLUE			"\033[1;34m"
# define LPURPLE		"\033[1;35m"
# define LCYAN			"\033[1;36m"
# define LWHITE			"\033[1;37m"
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
	int					num;
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
	int			state;
	int			l_exit;
	char		**path;
	char		**envs;
	t_env		*env;
	pid_t		*childs;
	t_comand	*comands;
	t_section	*sections;
}	t_mshell;

t_mshell	*g_mini;

// add_segtion.c //
void		add_segtion(char *str, int check);

// analyze_line.c //
void		free_comand(void);
void		free_sections(void);
int			analyze_line(char *line);

// builtin.c //
int			is_builtin(char *str);
int			run_builtin(t_comand *com);

// close_fd.c //
void		ft_reset_main_fd(void);
void		ft_close_fd(int fd_in);
void		ft_free_fd(void);

// ft_set_fd.c //
int			*build_tunnel(t_comand *com);
void		check_fd(t_comand *new, t_section *now);
void		not_comand(t_section *now);

// ft_set_mini_fd.c //
void		mini_check_fd(t_section *now);

// env_2_str.c //
char		**find_path(char **enpv);
char		**env_2_str(void);

// exit.c //
void		ft_exit(t_comand *com);

// ft_cd.c //
int			ft_cd(char *line);

//ft_count_exe.c //
t_section	*add_part(t_comand *new, t_section *now);
t_section	*add_comand(t_section *aux, t_comand *new);
void		set_up_comand(void);

// ft_echo.c //
int			ft_echo(t_comand *com);

// ft_env.c //
int			env_collec(char **env);
void		new_env(char *str, int num);
int			ft_env(t_comand *com);

// ft_execv.c //
void		ft_run(t_comand *com);
int			ft_execv(void);

// ft_expand.c //
int			check_name(char *str);
char		*str_expand(char *str);

// ft_export_no_args.c //
int			ft_export_no_args(t_comand *com);

// ft_export.c //
int			ft_export(char **comand);

// ft_here_doc.c //
int			here_doc(t_section *arv, int check);

// ft_puterror.c //
void		send_error(int n, char *str);
void		ft_puterror(char *funtion, char *str);

// ft_pwd.c //
int			ft_pwd(t_comand *com);

// ft_type.c //
void		assign_type(void);

// ft_unset.c //
void		unset_mini(void);
int			ft_unset(char *str);

// get_env_value.c //
char		*get_env_value(char *env_name);

// init_mini.c //
void		init_mini(char **env);

//  line_treatment.c //
int			word_width(char *str);
int			check_quotes(char *line);
void		ft_line_treatment(char *line);

// minishell.c //
int			main(int arc, char **arv, char **env);

// shlvlup.c //
void		shlvlup(void);
char		**ft_split_ignore(char const *s, char c);

// signal_tools.c //
void		signal_handler(int sig);
void		signal_child(void);
void		signal_heredoc(int sig);
int			signal_initialize(void);

#endif
