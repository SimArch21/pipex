/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:28:04 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/21 11:35:42 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
//int	dup2(int oldfd, int newfd);
//int	dup2(int the_one_where_we_really_write, int the_current_one);

//in this function, if we can't open the infile, we send an error msg to say 
//that it was not possible to open it. We don't execute the first command
//BUT we have to execute the other command and to put the result in the outfile
//as the terminal is working
//if we can't open the infile, it returns 1. 0 if everything works well
//if we can't open the file, we have to create the pipe and duplicate
//the READ_END part. Otherwise, the programm will remain in execution 
//without having finished it. =>This is a way to avoid this issue
//STDIN Reads and the STDOUD Writes
int	manage_infile(char *infile)
{
	int		fd;
	int		pipe_fd[2];

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
		if (pipe(pipe_fd) == -1)
			print_error("pipe failed");
		close(pipe_fd[WRITE_END]);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[READ_END]);
		return (1);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (0);
	}
}

//I had to create this function for the one below
//Because I had more than 25 lines and the norminette wasn't happy
void	parent_process(int pipe_fd_write, int pipe_fd_read)
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
	char	*cmd_path;
	char	**array_cmd;

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed");
	pid = fork();
	if (pid == -1)
		print_error("fork failed");
	else if (pid == 0)
	{
		close(pipe_fd[READ_END]);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
		cmd_path = create_command(cmd, env);
		array_cmd = ft_split(cmd, ' ');
		if (!array_cmd || !cmd_path)
			print_error("failed to create the command or to create the path");
		if (execve(cmd_path, array_cmd, env) == -1)
			print_error("execve failed");
	}
	else
		parent_process(pipe_fd[WRITE_END], pipe_fd[READ_END]);
}

void	manage_outfile(char *outfile, char *last_cmd, char **env, int heredoc)
{
	int		fd_outfile;
	int		pipe_fd[2];
	int		pid;
	char	*cmd_path;
	char	**array_cmd;

	pid = fork();
	if (pid == -1)
		print_error("fork failed");
	else if (pid == 0)
	{
		close(pipe_fd[READ_END]);
		if (heredoc == 0)
			fd_outfile = open(outfile, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			fd_outfile = open(outfile, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd_outfile == -1)
			print_error("open failed");
		dup2(fd_outfile, STDOUT_FILENO)
		close(fd_outfile);
		cmd_path = create_command(last_cmd, env);
		array_cmd = ft_split(last_cmd, ' ');
		if (execve(cmd_path, array_cmd, env) == -1)
			print_error("execve failed");
	}
}

//we have to execute the wait(NULL) at the end
//otherwise if we execute several the sleep cmd, it won't act as in the terminal
//Example: < infile sleep 5 | sleep 5 | ls -l > outfile
//=>it lasts only 5 seconds instead of 10 in the bash/terminal
//if we execute the wait(NULL) each time at the beginning of the parent process
//to make the child process finish, it will work but will lasts 10 seconds
//so it will work but differently as the bash
int	main(int argc, char **argv, char **env)
{
	int		i;
	int		j;
	int		heredoc;
	int		status;

	if (argc < 5)
		print_error("please follow this instructions: \
				./pipex infile 'cmd1' 'cmd2' 'cmd..' outfile");
	i = 1;
	j = 1;
	heredoc = 0;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		get_lines_from_heredoc(argv[2]);
		heredoc = 1;
		i++;
	}
	else if (manage_infile(argv[1]) == 1)
		i++;
	while (++i < argc - 2)
		manage_command(argv[i], env);
	manage_outfile(argv[argc - 1], argv[i], env, heredoc);
	while (++j < argc - 1)
		wait(&status);
	return (0);
}
