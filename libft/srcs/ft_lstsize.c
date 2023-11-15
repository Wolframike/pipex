/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 07:27:11 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/22 22:29:12 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_lstsize(t_list *lst)
{
	size_t	l;

	if (lst == NULL)
		return (0);
	l = 1;
	while (lst -> next != NULL)
	{
		lst = lst -> next;
		l++;
		if (l == INT_MAX)
			return (-1);
	}
	return ((int)l);
}
