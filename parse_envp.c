/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:25:10 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/17 18:29:35 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src)
		return (dest);
	while (i < n)
	{
		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dest);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
		((unsigned char *)ptr)[i++] = (unsigned char)value;
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset((char *)s, 0, n);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc(size * num);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * num);
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *str1)
{
	int		len;
	char	*ptr;
	
	len = ft_strlen(str1);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	return (ft_memcpy(ptr, str1, len + 1));
}

char	**arr_dup(char **enviroment)
{
	int		c;
	int		size;
	char	**envp;
	
	size = 0;
	while (enviroment[size] != NULL)
		size++;
	envp = (char **)malloc(sizeof(char *) * size);
	envp[size] = NULL;
	c = 0;
	while (c++ < size)
		envp[c - 1] = ft_strdup(enviroment[c - 1]);
	return (envp);
}