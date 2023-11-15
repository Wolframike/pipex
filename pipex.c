/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:08:00 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/31 17:53:23 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ppx_exec_cmd(char *command, char **envp)
{
	char	**command_exec;
	size_t	i;

	command_exec = ft_split(command, ' ');
	if (command_exec == NULL)
		ppx_exit(false, "malloc", ENOSET);
	if (command_exec[0] == NULL)
		ppx_exit(false, command, ENOCMD);
	if (command_exec[0][0] != '/')
		command_exec[0] = ppx_get_path(command_exec[0], envp);
	i = 0;
	if (command_exec[0] == NULL)
	{
		while (command_exec[i] != NULL)
			free(command_exec[i++]);
		free(command_exec);
		ppx_exit(false, command, ENOCMD);
	}
	execve(command_exec[0], command_exec, envp);
}

static void	ppx_parse_args(int argc, char **argv, bool *here_doc)
{
	bool	i;
	bool	o;

	if (argc < 5)
		ppx_exit(false, "pipex", EINVAL);
	*here_doc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	i = ((access(argv[1], R_OK) == 0) || here_doc);
	o = ((access(argv[argc - 1], W_OK) == 0)
			|| (access(argv[argc - 1], F_OK) < 0));
	if (!i)
	{
		errno = EACCES;
		if (access(argv[1], F_OK) < 0)
			errno = ENOENT;
		perror(argv[1]);
	}
	if (!o)
	{
		errno = EACCES;
		perror(argv[argc - 1]);
	}
	if (!i || !o)
		exit(EXIT_FAILURE);
}

static void	pipex(char *command, char **envp, int fdout, bool last)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ppx_exit(false, "pipe", EPIPE);
	pid = fork();
	if (pid < 0)
		ppx_exit(false, "fork", ENOSET);
	if (pid == 0 && last)
	{
		dup2(fdout, fd[1]);
		close(fdout);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ppx_exec_cmd(command, envp);
		ppx_exit(false, "execve", ENOSET);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fdin;
	int		fdout;
	int		i;
	bool	here_doc;

	ppx_parse_args(argc, argv, &here_doc);
	if (here_doc)
	{
		if (!ppx_open(argc, argv, NULL, &fdout))
			ppx_exit(false, "open", ENOSET);
		ppx_here_doc(argv, envp);
	}
	else
	{
		if (!ppx_open(argc, argv, &fdin, &fdout))
			ppx_exit(false, "open", ENOSET);
		dup2(fdin, STDIN_FILENO);
	}
	i = here_doc;
	while (i++ < argc - 3)
		pipex(argv[i + 1], envp, fdout, i == argc - 3);
	i = 0;
	while (i++ < argc - 3)
		wait(NULL);
	ppx_exit(true, NULL, ENOSET);
}
