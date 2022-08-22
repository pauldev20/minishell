# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 10:07:41 by mhedtman          #+#    #+#              #
#    Updated: 2022/08/22 16:59:19 by mhedtman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# the output name of the executable/archive
NAME = minishell

LIBFT = libft/libft.a

# compiler flags
CFLAGS	= #-Wall -Werror -Wextra

# the compiler to be used
CC	= cc

INCLUDES = -I${HOME}/.brew/Cellar/readline/8.1.2/include -Ilibft -Iincludes

LDFLAGS = -L${HOME}/.brew/Cellar/readline/8.1.2/lib -lreadline -Llibft -lft -g -fsanitize=address,undefined

# all the src/.c files that need to be compiled
SRCS =	src/main.c \
		src/minishell.c \
		src/helpers.c	\
		src/promt.c	\
		src/signal.c	\
		src/env/env.c	\
		src/env/helpers.c	\
		src/parser/sh_like_parser.c \
		src/parser/parser_helper.c \
		src/parser/tokens.c \
		src/builtins/builtin.c	\
		src/builtins/echo.c	\
		src/builtins/exit.c	\
		src/builtins/env.c	\
		src/builtins/export.c	\
		src/builtins/pwd.c	\
		src/builtins/unset.c

# replace .c with .o -> $(var:pattern=replacement)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

# this rule is responsible for building the executable/archive. It uses the built-in rule: ($(CC) $(CPPFLAGS) $(CFLAGS) -c -o x.o x.c) because .o prerequisites
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C libft

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug:
	$(MAKE) CFLAGS='-g' re

# remove the .o files
clean:
	$(MAKE) clean -C libft
	rm -rf $(OBJS)

# remove the .o and .a files
fclean: clean
	$(MAKE) fclean -C libft
	rm -rf $(NAME)

# remove all files and remake all
re: fclean all
	
.PHONY:	all bonus clean fclean re debug
