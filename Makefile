# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 10:07:41 by mhedtman          #+#    #+#              #
#    Updated: 2022/10/05 16:38:50 by mhedtman         ###   ########.fr        #
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

INCLUDES = -I$(DOWNLOADFOLDER)/readline_out/include -Ilibft -Iincludes
LDFLAGS = -L$(DOWNLOADFOLDER)/readline_out/lib -lreadline -Llibft -lft

# all the src/.c files that need to be compiled
SRCS =	src/main.c \
		src/minishell.c \
		src/catch_tty.c \
		src/helpers.c	\
		src/prompt.c	\
		src/signal.c	\
		src/error.c	\
		src/execute.c \
		src/here_doc.c \
		src/io_modification.c \
		src/token_modification.c \
		src/execute_builtins.c \
		src/pipex.c \
		src/env/env.c	\
		src/env/helpers.c	\
		src/parser/parser.c \
		src/parser/lexer.c \
		src/parser/expander.c \
		src/parser/expander_utils.c \
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

# colors
HIGHIWHITE = \033[0;97m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m

all: $(NAME)

$(DOWNLOADFOLDER):
	@echo "$(YELLOW)STARTING DOWNLOAD(s)...$(NC)"
	@mkdir -p dwnlds
	@curl -s https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output dwnlds/readline-8.1.2.tar.gz > /dev/null
	@tar xfz dwnlds/readline-8.1.2.tar.gz -C dwnlds
	@echo "$(YELLOW)STARTING DOWNLOAD(s)...$(NC)"
	@cd dwnlds/readline-8.1.2; ./configure --prefix=$(PWD)/dwnlds/readline_out > /dev/null; cd ../../;
	@cd $(DOWNLOADFOLDER)/readline-8.1.2; make -s > /dev/null 2> /dev/null; make -s install > /dev/null 2> /dev/null;
	@echo "$(GREEN)FINISHED DOWNLOAD(s)...$(NC)"

# this rule is responsible for building the executable/archive. It uses the built-in rule: ($(CC) $(CPPFLAGS) $(CFLAGS) -c -o x.o x.c) because .o prerequisites
$(NAME): $(DOWNLOADFOLDER) $(OBJS) $(LIBFT)
	@echo	"$(GREEN)LINKING: $(HIGHIWHITE)minishell...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo	"$(GREEN)FINISHED...$(NC)"

$(LIBFT):
	@echo	"$(GREEN)COMPILING: $(HIGHIWHITE)libft...$(NC)"
	@$(MAKE) -s bonus -C libft

%.o : %.c
	@echo "$(GREEN)COMPILING: $(HIGHIWHITE)$<...$(NC)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug:
	$(MAKE) CFLAGS='-g -fsanitize=address,undefined' re

# remove the .o files
clean:
	@echo "$(GREEN)CLEANING...$(NC)"
	@$(MAKE) -s clean -C libft
	@rm -rf $(OBJS)

# remove the .o and .a files
fclean: clean
	@echo "$(GREEN)F-CLEANING...$(NC)"
	@$(MAKE) -s fclean -C libft
	@rm -rf $(NAME)
	@rm -rf $(DOWNLOADFOLDER)

# remove all files and remake all
re: fclean all

.PHONY:	all bonus clean fclean re debug
