/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:10:34 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/08 12:41:22 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newlstel;

	newlst = NULL;
	if (!lst)
		return (NULL);
	while (1)
	{
		if (!lst)
			newlstel = ft_lstnew(lst->content);
		else
			newlstel = ft_lstnew(f(lst->content));
		if (!newlstel)
		{
			if (newlst)
				ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newlstel);
		if (lst->next != NULL)
			lst = lst->next;
		else
			break ;
	}
	return (newlst);
}
