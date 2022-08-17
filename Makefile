# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 10:07:41 by mhedtman          #+#    #+#              #
#    Updated: 2022/08/17 20:13:58 by pgeeser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# the output name of the executable/archive
NAME = minishell

LIBFT = libft/libft.a

# compiler flags
CFLAGS	= -Wall -Werror -Wextra

# the compiler to be used
CC	= cc

INCLUDES = -Ilibft -Iincludes

LDFLAGS = -lreadline -Llibft -lft

# all the src/.c files that need to be compiled
SRCS =	src/main.c \
		src/minishell.c \
		src/helpers.c

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

# remove the .o files
clean:
	rm -rf $(OBJS)

# remove the .o and .a files
fclean: clean
	rm -rf $(NAME)

# remove all files and remake all
re: fclean all
	
.PHONY:	all bonus clean fclean re
