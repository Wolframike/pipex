/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 05:09:06 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/30 18:02:38 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include "libft/includes/libft.h"

# define ENOSET 0
# define ENOCMD -1
# define EBADSUB -2
# define PERMS 0644

void	ppx_exit(bool success, char *msg, int err);
char	*ft_strndup(const char *src, size_t n);
bool	ppx_isvalid_varchar(char c);
char	*ppx_get_path(char *command, char **envp);
bool	ppx_open(int argc, char **argv, int *fdin, int *fdout);
void	ppx_here_doc(char **argv, char **envp);

#endif