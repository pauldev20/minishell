/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:25:36 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/02 23:43:46 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
