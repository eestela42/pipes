/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestela <eestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:20:18 by eestela           #+#    #+#             */
/*   Updated: 2022/01/10 19:20:21 by eestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*for_for_access(char **path, char *join, int i, char *cmd)
{
	i = 0;
	if (!path)
		return (NULL);
	while (path[i] != 0)
	{
		if (ft_strend_is(path[i], "/") == 0)
			path[i] = ft_strjoin_free(path[i], "/");
		join = ft_strjoin(path[i], cmd);
		if (access(join, F_OK | X_OK) == 0)
		{
			free(cmd);
			free_comm(path);
			return (join);
		}
		free(join);
		i++;
	}
	return (NULL);
}

char	*for_access(char *cmd)
{
	int			i;
	char		**path;
	char		*join;
	extern char	**environ;

	i = -1;
	path = NULL;
	join = NULL;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], "PATH=", 5))
		{
			path = ft_split(environ[i] + 5, ':');
			break ;
		}	
	}
	join = for_for_access(path, join, i, cmd);
	if (join)
		return (join);
	free(cmd);
	if (path)
		free_comm(path);
	return (NULL);
}

void	child_process(char *f1, char *cmd1, int *tube, char **environ)
{
	int		fd;
	char	**command;

	fd = open(f1, O_RDONLY);
	if (fd == -1)
		ft_error("Erreur d'ouverture du fichier d'entre");
	if (!cmd1[0] || cmd1[0] == ' ')
		ft_error("Commande 1 invalide");
	command = ft_split(cmd1, ' ');
	if (!command)
		ft_error("Commande 1 invalide");
	command[0] = for_access(command[0]);
	if (!command[0])
	{
		free_comm(command);
		ft_error("Commande 1 invalide");
	}
	close(tube[0]);
	dup2(tube[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(tube[1]);
	close(fd);
	if (command[0])
		execve(command[0], command, environ);
	free_comm(command);
}

void	parent_process(char *f2, char *cmd2, int *tube, char **environ)
{
	int		fd;
	char	**command;

	fd = open(f2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Erreur d'ouverture ou de creation du fichier de sortie");
	if (!cmd2[0] || cmd2[0] == ' ')
		ft_error("Commande 2 invalide");
	command = ft_split(cmd2, ' ');
	if (!command)
		ft_error("Commande 2 invalide");
	command[0] = for_access(command[0]);
	if (!command[0])
	{
		free_comm(command);
		ft_error("Commande 2 invalide");
	}
	close(tube[1]);
	dup2(tube[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(tube[0]);
	close(fd);
	if (command[0])
		execve(command[0], command, environ);
	free_comm(command);
}

int	main(int ac, char **av, char **environ)
{
	int			tube[2];
	pid_t		pid;

	if (!environ[0])
		ft_error("Erreur lors de l'acces au path");
	if (ac != 5)
		ft_error("Mauvais nombre d'argument");
	pipe(tube);
	pid = fork();
	if (pid < 0)
		ft_error("Erreur du fork");
	if (pid == 0)
		child_process(av[1], av[2], tube, environ);
	else
		parent_process(av[4], av[3], tube, environ);
}
