/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:29:17 by pgeeser           #+#    #+#             */
/*   Updated: 2022/09/28 15:13:43 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
// size_t	ft_strlen(const char *str);
// void	*ft_memset(void *ptr, int value, size_t num);
// int		ft_strcmp(char *s1, char *s2);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strjoin(char *s1, char *s2);
// char	*strchr(const char *str, int character);

#endif