/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 07:38:21 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/21 18:37:42 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*bef;
	t_list	*cur;

	if (del == NULL || lst == NULL || *lst == NULL)
		return ;
	cur = *lst;
	while (cur -> next != NULL)
	{
		bef = cur;
		cur = cur -> next;
		(*del)(bef -> content);
		free(bef);
	}
	(*del)(cur -> content);
	free(cur);
	*lst = NULL;
}
