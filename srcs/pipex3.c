/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:52:13 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/16 16:15:53 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	manage_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		perror("open failed");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	manage_command(char *argv, char **env)
{
	int		pid;
	int		pipe_fd[2];
	char	*cmd_path;
	char	**array_cmd;

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed");
	pid = fork();
	if (pid < 0)
		print_error("fork failed");
	if (pid == 0)
	{
		close(pipe_fd[READ_END]);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
		cmd_path = create_command(argv, env);
		array_cmd = ft_split(argv, ' ');
		if (!cmd_path || !array_cmd)
			print_error("failed to create the command");
		if (execve(cmd_path, array_cmd, env) == -1)
			print_error("execve failed");
	}
	else
	{
		close(pipe_fd[WRITE_END]);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[READ_END]);
	}
}

void	manage_outfile(char *outfile, char *cmd, char **env)
{
	int		pid;
	int		pipe_fd[2];
	char	*cmd_path;
	char	**array_cmd;
	int		fd;

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed");
	pid = fork();
	if (pid < 0)
		print_error("pipe failed");
	if (pid == 0)
	{
		fd = open(outfile, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd < 0)
			print_error("failed to open the outfile");
		close(pipe_fd[READ_END]);
		dup2(fd, STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
		close(fd);
		cmd_path = create_command(cmd, env);
		array_cmd = ft_split(cmd, ' ');
		if (!cmd_path || !array_cmd)
			print_error("failed to create the command");
		if (execve(cmd_path, array_cmd, env) == -1)
			print_error("execve failed");
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;

	manage_infile(argv[1]);
	i = 1;
	while (++i < argc - 3)
	{
		manage_command(argv[i], env);
	}
	manage_outfile(argv[argc - 1], argv[i], env);
	return (0);
}
