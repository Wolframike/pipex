/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:39:00 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/30 18:08:17 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ppx_find_dir(char *command, char *path)
{
	size_t	i;
	char	*cmddir;
	char	*cmdpath;

	i = 0;
	while (path[i] != ':' && path[i] != '\0')
		i++;
	if (i == 0)
		return (NULL);
	cmddir = ft_strndup(path, i + 1);
	if (cmddir == NULL)
		ppx_exit(false, "malloc", ENOSET);
	cmddir[i] = '/';
	cmdpath = ft_strjoin(cmddir, command);
	free(cmddir);
	if (cmdpath == NULL)
		ppx_exit(false, "malloc", ENOSET);
	if (access(cmdpath, X_OK) == 0)
		return (cmdpath);
	free(cmdpath);
	return (NULL);
}

static char	*ppx_format_env(char **envp)
{
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	path = ft_strjoin(path, ":");
	return (path);
}

char	*ppx_get_path(char *command, char **envp)
{
	char	*path;
	char	*cmdpath;

	if (command[0] == '.')
	{
		if ((access(command, F_OK) != 0))
			ppx_exit(false, command, ENOENT);
		if (access(command, X_OK) != 0)
			ppx_exit(false, command, EACCES);
		return (command);
	}
	path = ppx_format_env(envp);
	if (path == NULL)
		ppx_exit(false, command, ENOENT);
	cmdpath = NULL;
	while (*path != '\0')
	{
		cmdpath = ppx_find_dir(command, path);
		if (cmdpath != NULL)
			return (cmdpath);
		while (*path != ':' && *path != '\0')
			path++;
		path += (*path == ':');
	}
	return (cmdpath);
}

bool	ppx_open(int argc, char **argv, int *fdin, int *fdout)
{
	if (fdin != NULL)
	{
		*fdin = open(argv[1], O_RDONLY);
		if (*fdin == -1)
			return (false);
		*fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, PERMS);
	}
	else
		*fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, PERMS);
	if (*fdout == -1)
	{
		if (fdin != NULL)
			close(*fdin);
		return (false);
	}
	return (true);
}
