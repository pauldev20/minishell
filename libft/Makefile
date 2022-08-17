# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 15:59:47 by pgeeser           #+#    #+#              #
#    Updated: 2022/05/09 13:15:15 by pgeeser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# the output name of the executable/archive
NAME = libft.a

# compiler flags
CFLAGS = -Wall -Werror -Wextra

# the compiler to be used
CC = cc

# all the src/.c files that need to be compiled
SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c\
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_tolower.c ft_toupper.c\
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c\
		ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_digits_of_int.c ft_digits_of_hex.c

BONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

# replace .c with .o -> $(var:pattern=replacement)
OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(BONUS:.c=.o)


# *Rules*
# targets : prerequisites

# this rule is responsible for building the executable/archive. It uses the built-in rule: ($(CC) $(CPPFLAGS) $(CFLAGS) -c -o x.o x.c) because .o prerequisites
$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

all: $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
	ar rc $(NAME) $(OBJS) $(OBJS_BONUS)

# remove the .o files
clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

# remove the .o and .a files
fclean: clean
	rm -rf $(NAME)

# remove all files and remake all
re: fclean all

norm:
	norminette *.c *.h

.PHONY:	all bonus clean fclean re norm