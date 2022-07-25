/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioriola <ioriola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:56:28 by alsanche          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/24 16:41:46 by alsanche         ###   ########lyon.fr   */
=======
/*   Updated: 2022/07/23 11:10:30 by ioriola          ###   ########.fr       */
>>>>>>> 0d8a12dd9f5614f49175d4a199478bac45d38cb1
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
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define MAGENTA "\033[1;35m"
<<<<<<< HEAD
# define RESET_C "\033[0m"
=======
# define RESET ">\033[0m" 
>>>>>>> 0d8a12dd9f5614f49175d4a199478bac45d38cb1

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

/* env.c */

int		env_collec(char **env, t_mshell *mini);
void	new_env(char *str, int num, t_mshell *mini);
void	print_env(t_mshell *mini);

/* env_2_str.c */

char	**env_2_str(t_mshell *mini);

/* export.c */

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