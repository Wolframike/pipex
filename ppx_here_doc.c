/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:31:37 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/31 04:56:16 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ppx_varlen(char **line, bool *braces)
{
	size_t	l;

	l = 1;
	*braces = false;
	if ((*line)[l] == '{')
	{
		*braces = true;
		l++;
	}
	while (ppx_isvalid_varchar((*line)[l]) && (*line)[l] != '\0')
		l++;
	return (l);
}

static void	ppx_write_envvar(char **line, int fdout, char **envp)
{
	size_t	l;
	bool	braces;

	l = ppx_varlen(line, &braces);
	if (l == 1)
	{
		ft_putchar_fd('$', fdout);
		return ;
	}
	if (braces && (*line)[l] != '}')
	{
		free(*line);
		ppx_exit(false, "heredoc", EBADSUB);
	}
	l += braces;
	while ((*envp != NULL)
		&& ((ft_strncmp((*line) + 1 + braces, *envp, l - 1 - braces * 2) != 0)
			|| ((*envp)[l - 1 - braces * 2] != '=')))
		envp++;
	if (*envp != NULL)
		ft_putstr_fd(*envp + (l - braces * 2), fdout);
	(*line) += (l - 1);
}

static void	ppx_write_stdin(char *line, int fdout, char **envp)
{
	while (*line != '\0')
	{
		if (*line == '$')
			ppx_write_envvar(&line, fdout, envp);
		else
			ft_putchar_fd(*line, fdout);
		line++;
	}
}

static bool	ppx_stdin_loop(char **argv, int fd[2], char **envp)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (line == NULL)
	{
		close(fd[1]);
		ppx_exit(false, "get_next_line", ENOSET);
	}
	if ((ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		&& ft_strlen(line) == ft_strlen(argv[2]) + 1)
	{
		free(line);
		return (true);
	}
	ppx_write_stdin(line, fd[1], envp);
	free(line);
	return (false);
}

void	ppx_here_doc(char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ppx_exit(false, "pipe", EPIPE);
	pid = fork();
	if (pid == -1)
		ppx_exit(false, "fork", ENOSET);
	if (pid == 0)
	{
		close(fd[0]);
		while (true)
		{
			ft_putstr_fd("pipex heredoc> ", STDOUT_FILENO);
			if (ppx_stdin_loop(argv, fd, envp))
				ppx_exit(true, NULL, ENOSET);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}
