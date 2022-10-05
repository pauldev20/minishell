# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 10:07:41 by mhedtman          #+#    #+#              #
#    Updated: 2022/10/05 13:18:54 by mhedtman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# the output name of the executable/archive
NAME = minishell

LIBFT = libft/libft.a

DOWNLOADFOLDER = dwnlds

# compiler flags
CFLAGS	= #-Wall -Werror -Wextra

# the compiler to be used
CC	= cc

INCLUDES = -I$(DOWNLOADFOLDER)/readline_out/include -Ilibft -Iincludes -g -fsanitize=address,undefined
LDFLAGS = -L$(DOWNLOADFOLDER)/readline_out/lib -lreadline -Llibft -lft

# all the src/.c files that need to be compiled
SRCS =	src/main.c \
		src/minishell.c \
		src/catch_tty.c \
		src/helpers.c	\
		src/promt.c	\
		src/signal.c	\
		src/error.c	\
		src/execute.c \
		src/execute_builtins.c \
		src/pipex.c \
		src/env/env.c	\
		src/env/helpers.c	\
		src/parser/parser.c \
		src/parser/lexer.c \
		src/parser/expander.c \
		src/parser/pipe_expander.c \
		src/builtins/builtin.c	\
		src/builtins/echo.c	\
		src/builtins/cd.c \
		src/builtins/exit.c	\
		src/builtins/env.c	\
		src/builtins/export.c	\
		src/builtins/pwd.c	\
		src/builtins/unset.c \

# replace .c with .o -> $(var:pattern=replacement)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(DOWNLOADFOLDER):
	@echo "dwonloading things ..."
	@mkdir -p dwnlds
	@curl https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output dwnlds/readline-8.1.2.tar.gz
	@tar xvfz dwnlds/readline-8.1.2.tar.gz -C dwnlds
	@@cd dwnlds/readline-8.1.2; ./configure --prefix=$(PWD)/dwnlds/readline_out; cd ../../;
	@@cd $(DOWNLOADFOLDER)/readline-8.1.2; make; make install;
	@echo "finished downloading readline lib..."

# this rule is responsible for building the executable/archive. It uses the built-in rule: ($(CC) $(CPPFLAGS) $(CFLAGS) -c -o x.o x.c) because .o prerequisites
$(NAME): $(DOWNLOADFOLDER) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	@echo	"compiling: libft ..."
	$(MAKE) bonus -C libft

%.o : %.c
	@echo "compiling: $< ..."
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
	rm -rf $(DOWNLOADFOLDER)

# remove all files and remake all
re: fclean all

.PHONY:	all bonus clean fclean re debug
