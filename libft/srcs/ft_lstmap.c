/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 07:54:05 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/28 20:55:42 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*flm_helper(t_list *temp, t_list *head, void (*del)(void *))
{
	if (temp == NULL)
	{
		ft_lstclear(&head, del);
		return (NULL);
	}
	ft_lstadd_back(&head, temp);
	return (head);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*temp;

	if (f == NULL || lst == NULL || del == NULL)
		return (NULL);
	head = ft_lstnew((*f)(lst -> content));
	if (head == NULL)
		return (NULL);
	if (lst -> next == NULL)
		return (head);
	lst = lst -> next;
	while (lst -> next != NULL)
	{
		temp = ft_lstnew((*f)(lst -> content));
		if (flm_helper(temp, head, del) == NULL)
			return (NULL);
		lst = lst -> next;
	}
	temp = ft_lstnew((*f)(lst -> content));
	if (flm_helper(temp, head, del) == NULL)
		return (NULL);
	return (head);
}
