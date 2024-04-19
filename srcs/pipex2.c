/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:28:04 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/18 16:08:21 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
//int	dup2(int oldfd, int newfd);
//int	dup2(int the_one_where_we_write, int the_current_one);
//💡 you have to do CTRL + D to go out from the heredoc/cat command

//in this function, if we can't open the infile, we send an error msg to say 
//that it was not possible to open it. We don't execute the first command
//BUT we have to execute the other command and to put the result in the outfile
//as the terminal is working
int	manage_infile(char *infile)
{
	int	fd;
//il faut que tu rajoutes la partie lorsque l'on doit sauter la premiere commande car il n'y a pas de infile
//mais que l'on doit quand meme executer la seconde commande
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
/*		close(pipe_fd[READ_END]);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
		cmd_path = create_command(cmd, env);
		array_cmd = ft_split(cmd, ' ');
		if (!array_cmd || !cmd_path)
			print_error("failed to create array_cmd");
		if (execve(cmd_path, array_cmd, env) == -1)
			print_error("execve failed");
*/
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	go_out_from_heredoc(char *line, char *heredoc_limiter)
{
	int		i;
	size_t	ctr;

	i = 0;
	ctr = 0;
	while (heredoc_limiter[i])
	{
		if (heredoc_limiter[i] == line[i])
			ctr++;
		else
			ctr = 0;
		i++;
	}
	if (ft_strlen(line) - 1 == ft_strlen(heredoc_limiter)
		&& ft_strlen(line) - 1 == ctr)
		return (1);
	return (0);
}

void	get_lines_from_heredoc(char *limiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
//		if (!line)
//			print_error("failed with GNL");
		if (go_out_from_heredoc(line, limiter))
		{
			break ;
		}
		ft_putstr_fd(line, pipe_fd[WRITE_END]);
		free(line);
	}
	//free(line);
	close(pipe_fd[WRITE_END]);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(pipe_fd[READ_END]);
}

//if the line is exactly the same as the here_doc's LIMITER
//we close the here_doc
//argv[1] is here_doc and argv[2] is the LIMITER
//it was hard to understand when to go out from the here_doc, but I succeed and I'm still alive
//you have to use write function before and after your go_out_from_heredoc function to really understand it 
/*void	manage_here_doc(char **argv)
{
	char	*line;
	int		pipe_fd[2];
//	char	*cmd_path;
//	char	**array_cmd;

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed");
	while (1)
	{
		line = get_next_line(0);
//		if (!line)
//			print_error("failed with GNL");
		if (go_out_from_heredoc(line, argv[2]))
		{
			break ;
		}
		ft_putstr_fd(line, pipe_fd[WRITE_END]);
	}
	ft_putstr_fd(line, pipe_fd[WRITE_END]);
	dup2(pipe_fd[WRITE_END], STDIN_FILENO);
	close(pipe_fd[WRITE_END]);
}*/

/*void	manage_heredoc(char **argv)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed");
	pid = fork();
	if (pid < 0)
		print_error("fork failed");
	if (pid == 0)
	{
		get_lines_from_heredoc(argv[2], pipe_fd[WRITE_END]);
//		close(pipe_fd[READ_END]);
//		dup2(pipe_fd[WRITE_END], STDIN_FILENO);
//		close(pipe_fd[WRITE_END]);
	}
	else
	{
		close(pipe_fd[READ_END]);
		dup2(pipe_fd[READ_END], STDOUT_FILENO);
		wait(NULL);
	}
}*/

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
			print_error("failed to create array_cmd");
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
	int		fd;
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
		fd = open(outfile, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd == -1)
			print_error("open failed");
		if (dup2(fd, STDOUT_FILENO) == -1)
			print_error("dup2 failed");
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
	int	j;

	if (argc < 5)
		print_error("please follow this instructions: \
				./pipex infile 'cmd1' 'cmd2' 'cmd..' outfile");
	i = 1;
	j = 1;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
//		write(2, "before", 6);
		get_lines_from_heredoc(argv[2]);
//		write(2, "after", 5);
		i++;
	//now your goal is to go out from the cat command
	//you have to write what's in the here_doc into the pipe
	}
	else
		manage_infile(argv[1]);
	while (++i < argc - 2)
		manage_command(argv[i], env);
	manage_outfile(argv[argc - 1], argv[i], env);
	while (++j < argc - 3)
		wait(NULL);
	return (0);
}






















//when you open a pipe, this has 2 files descriptors where you can read and write
//simple function to know how to use the pipe function and the dup2 function
/*int	main(void)
{
	int		pip[2];
	char	buffer[256];
	int		outfile;

	pipe(pip);
	write(pip[WRITE_END], "my msg\n", 6);
	close(pip[WRITE_END]);
	read(pip[READ_END], buffer, 256);
	dup2(STDOUT_FILENO, pip[READ_END]);
	outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(outfile, STDOUT_FILENO);
	printf("%s\n", buffer);
	close(pip[READ_END]);
	return (0);
}*/

//Small examples to understand the access function
/*int main()
{
    char *filename = "infile";

    if (access(filename, F_OK) == 0)
        printf("The file \"%s\" exists.\n", filename);
    else
        printf("The file \"%s\" doesn't exists.\n", filename);

	if (access(filename, X_OK) == 0)
		printf("You have the rights to execute the \"%s\".\n", filename);
	else
		printf("You don't have the rights to execute the \"%s\".\n", filename);

    return (0);
}*/














/*
//on veut une fonction qui execute la premiere commande
//et qui ecrit le resultat dans la pipe
//le processus enfant s'occupe d'ecrire dans la pipe
void	child_process(int pipe_fd[2], char *argv, char **env)
{
	int		infile;
	char	**array_cmd;
	char	*cmd;

	close(pipe_fd[READ_END]);
	cmd = create_command(argv, env);
	array_cmd = ft_split(argv, ' ');
	if (!array_cmd || !cmd)
		print_error("failed with the commands");
	infile = open("infile", O_RDONLY);//this is not strictly correct
	if (infile == -1)
		print_error("open failed");
	dup2(infile, STDIN_FILENO);//this line is useful, otherwise the command won't execute
//	

//	dup2(STDOUT_FILENO, pipe_fd[WRITE_END]);//pour m'aider - a effacer
	//this redirects what we read from the pipe and to duplicate it into the command line (STDOUT_FILENO)
	
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);//this change the redirection of the next command
//	it should have printed on the command line (STDOUT_FILENO), but we duplicates it into the pipe

	if (execve(cmd, array_cmd, env) == -1)
		print_error("execve failed");
}

//in the parent process, we have to read 
void	parent_process(int pipe_fd[2], char *argv, char **env)
{
	int		outfile;
	char	**array_cmd;
	char	*cmd;

	close(pipe_fd[WRITE_END]);
	cmd = create_command(argv, env);
	array_cmd = ft_split(argv, ' ');
	if (!array_cmd || !cmd)
		print_error("failed with the commands");
//	printf("we reached this line 8\n");
	outfile = open("outfile", O_CREAT | O_WRONLY | O_TRUNC, 0644);//this is not strictly correct
	if (outfile == -1)
		print_error("open failed");
	dup2(outfile, STDOUT_FILENO);//this line is useful to redirect what we print from the STDOUT_FILENO into the outfile
	//if we comment it, the final result will be in the command line
//	printf("we reached this line 8.5\n");
	dup2(pipe_fd[READ_END], STDIN_FILENO);//this line is useful to finish the programm. Otherwise we will stay in this process without 
	//executing the last command
//	printf("we reached this line 9\n");
	if (execve(cmd, array_cmd, env) == -1)
		print_error("execve failed");
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		pipe_fd[2];
	int		pid;

	if (argc != 5)
		write(2, "we need 5 arguments\n", 20);
	i = 2;
//	printf("we reached this line 5\n");
	while (argv[i] && i < argc - 2)
	{
		if (pipe(pipe_fd) == -1)
			print_error("pipe failed");
		pid = fork();
		if (pid < 0)
			print_error("fork failed");
		if (pid == 0)//call child process
		{
//			printf("we reached this line 6\n");
			child_process(pipe_fd, argv[i], env); 
		}
		else//call parent process
		{
			wait(NULL);
//			printf("we reached this line 7\n");
			parent_process(pipe_fd, argv[i + 1], env);//on veut executer la seconde commande - cad argv[i + 1]
		}
		i++;
	}
//	printf("we reached this line 10\n");
	close(pipe_fd[WRITE_END]);
	close(pipe_fd[READ_END]);
	return (0);
}*/
