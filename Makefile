# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 10:07:41 by mhedtman          #+#    #+#              #
#    Updated: 2022/08/17 15:43:15 by mhedtman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# the output name of the executable/archive
NAME = minishell

# compiler flags
CFLAGS	= -Wall -Werror -Wextra

# the compiler to be used
CC	= cc

# all the src/.c files that need to be compiled
SRCS =	main.c \
		minishell.c \
		parse_envp.c

# replace .c with .o -> $(var:pattern=replacement)
OBJS = $(SRCS:.c=.o)

# this rule is responsible for building the executable/archive. It uses the built-in rule: ($(CC) $(CPPFLAGS) $(CFLAGS) -c -o x.o x.c) because .o prerequisites

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)

all: $(NAME)

# remove the .o files
clean:
	rm -rf $(OBJS)

# remove the .o and .a files
fclean: clean
	rm -rf $(NAME)

# remove all files and remake all
re: fclean all
	
.PHONY:	all bonus clean fclean re
