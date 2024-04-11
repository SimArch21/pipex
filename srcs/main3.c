/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:05:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/03/24 15:38:46 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//you need a function to retrieve the path from env
//then we want to add the slash
//we want a function to create the command like: /bin/ls

//in the main we create execute the pipe
//then we have to create the first subprocess
//then the second one
//close the fds[]

void	print_error(char *msg)
{
	perror(msg);
	exit(1);
}

char	*get_path_from_env(char **env)
{
	char	*path;

	path = ft_strdup("PATH=");
	while (*env)
	{
		if (ft_strncmp(*env, path, ft_strlen(path)) == 0)
			return (free(path), ft_strdup(*env + 5));
		env++;
	}
	return (free(path), NULL);
}

//we want to create the command
//we have to cut the path in subpaths
//then add the slash
//and join the argv[2]
char	*create_command(char *argv, char *path)
{
	char	**subpath;
	char	**array_cmd;
	char	*command;
	int		x;
	
	subpath = ft_split_for_slash(path, ':');
	array_cmd = ft_split(argv, ' ');
	x = 0;
	while (subpath[x])
	{
		command = ft_strjoin(subpath[x], *array_cmd);
		if (access(command, X_OK) == 0)
			return (free_array(subpath), free_array(array_cmd), command);
		x++;
		free(command);
	}
	return (free_array(subpath), free_array(array_cmd), NULL);
}

void	first_subprocess(int fds[2], char **argv, char **env, char *path)
{
	pid_t	pid;
	char	*command;
	char	**array_cmd;
	int		fd;

	pid = fork();
	if (pid == -1)
		print_error("fork failed");
	if (pid == 0)
	{
		close(fds[0]);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			print_error("open failed");
		dup2(fd, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		command = create_command(argv[2], path);
		array_cmd = ft_split(argv[2], ' ');
		if (execve(command, array_cmd, env) == -1)
			print_error("execve failed");
	}
}

void	second_subprocess(int fds[2], char **argv, char **env, char *path)
{
	pid_t	pid;
	char	*command;
	int		fd;
	char	**array_cmd;

	pid = fork();
	if (pid == -1)
		print_error("fork failed");
	if (pid == 0)
	{
		close(fds[1]);
		fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			print_error("open failed");
		dup2(fd, STDOUT_FILENO);
		dup2(fds[0], STDIN_FILENO);
		command = create_command(argv[3], path);
		array_cmd = ft_split(argv[3], ' ');
		if (execve(command, array_cmd, env) == -1)
			print_error("execve failed");
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*path;
	int		fds[2];

	path = get_path_from_env(env);
	if (pipe(fds) == -1)
		print_error("pipe failed");
	first_subprocess(fds, argv, env, path);
	wait(NULL);
	second_subprocess(fds, argv, env, path);
	argc = 0;
	return (free(path), close(fds[0]), close(fds[1]), 0);
}
