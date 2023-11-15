/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:01:30 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/30 18:12:30 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ppx_exit(bool success, char *msg, int err)
{
	if (success)
		exit(EXIT_SUCCESS);
	if (err == ENOCMD)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else if (err == EBADSUB)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": bad substitution\n", STDERR_FILENO);
	}
	else
	{
		if (err != ENOSET)
			errno = err;
		perror(msg);
	}
	exit(EXIT_FAILURE);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	l;

	l = ft_strlen(src);
	if (n < l)
		l = n;
	dest = (char *)malloc(sizeof(char) * (l + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, src, l + 1);
	return (dest);
}

bool	ppx_isvalid_varchar(char c)
{
	if (ft_isalnum(c) == 1)
		return (true);
	if (c == '_')
		return (true);
	return (false);
}
