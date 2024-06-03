/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernandoclaus <fernandoclaus@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:54:58 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/04/10 12:07:03 by fernandocla      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*container;
	t_list	*new;
	
	new = 0;
	while (lst)
	{
		container = ft_lstnew((*f)(lst->content));
		if(!container)
		{
			ft_lstclear(&container, del);
			return (0);
		}
		ft_lstadd_back(&new, container);
		lst = lst->next;
	}
	return (new);
}
