# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 15:07:42 by alsanche          #+#    #+#              #
#    Updated: 2022/09/04 18:12:23 by alsanche         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCDIR		= src
SRCS = 	$(SRCDIR)/analyze_line.c \
		$(SRCDIR)/add_segtion.c \
		$(SRCDIR)/builtin.c \
		$(SRCDIR)/env_2_str.c \
		$(SRCDIR)/ft_cd.c \
		$(SRCDIR)/ft_echo.c \
		$(SRCDIR)/ft_env.c \
		$(SRCDIR)/ft_expand.c \
		$(SRCDIR)/ft_export_no_args.c \
		$(SRCDIR)/ft_export.c \
		$(SRCDIR)/ft_puterror.c \
		$(SRCDIR)/ft_pwd.c \
		$(SRCDIR)/ft_type.c \
		$(SRCDIR)/ft_unset.c \
		$(SRCDIR)/get_env_value.c \
		$(SRCDIR)/init_mini.c \
		$(SRCDIR)/line_treatment.c \
		$(SRCDIR)/minishell.c \
		$(SRCDIR)/shlvlup.c

OBJS = $(SRCS:.c=.o)

GCC = gcc

FLAGS = -Wall -Werror -Wextra
DEBUG = -fsanitize=address -g3

LIBDIR		= lib
LIBFTDIR	= $(LIBDIR)/libft
LIBS		= -L$(LIBFTDIR) -lft -lreadline

INCLUDE		= -I. -I$(LIBDIR) -I$(LIBFTDIR) -I$(SRCDIR)

$(NAME): $(OBJS)
	$(GCC) -o $(NAME) $(OBJS) $(LIBS) $(DEBUG)

.PHONY: all re clean fclean

all:  $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(GCC) -o $@ -c $^ $(INCLUDE) $(FLAGS)
	