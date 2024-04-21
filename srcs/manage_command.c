/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:10:06 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/21 12:17:55 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child_process_to_pipe(int pipe_fd_write, int pipe_fd_read, \
			char *cmd, char **env)
{
	char	*cmd_path;
	char	**array_cmd;

	close(pipe_fd_read);
	dup2(pipe_fd_write, STDOUT_FILENO);
	close(pipe_fd_write);
	cmd_path = create_command(cmd, env);
	if (!cmd_path)
		print_error("failed to create cmd_path");
	array_cmd = ft_split(cmd, ' ');
	if (!array_cmd)
		print_error("failed to create array_cmd");
	if (execve(cmd_path, array_cmd, env) == -1)
		print_error("execve failed");
}

//I had to create this function for the one below
//Because I had more than 25 lines and the norminette wasn't happy
static void	parent_process(int pipe_fd_write, int pipe_fd_read)
{
	close(pipe_fd_write);
	dup2(pipe_fd_read, STDIN_FILENO);
	close(pipe_fd_read);
}

//	fildes[0] = READ_END;
//	fildes[1] = WRITE_END;
void	manage_command(char *cmd, char **env)
{
	int		pipe_fd[2];
	int		pid;

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed");
	pid = fork();
	if (pid == -1)
		print_error("fork failed");
	else if (pid == 0)
		child_process_to_pipe(pipe_fd[WRITE_END], pipe_fd[READ_END], cmd, env);
	else
		parent_process(pipe_fd[WRITE_END], pipe_fd[READ_END]);
}
