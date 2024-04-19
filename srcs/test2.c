/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:59:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/15 18:38:03 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	print_error(char *msg)
{
	perror(msg);
	exit(1);
}

//we want to store the whole PATH starting by the '/' in a variable
char	*get_path_from_env(char **env)
{
	int		i;
	char	*path_prefix;
	char	*result;

	path_prefix = ft_strdup("PATH=");
	if (!path_prefix)
		print_error("ft_strdup failed");
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], path_prefix, ft_strlen(path_prefix)) == 0)
		{
			free(path_prefix);
			result = ft_strdup(env[i] + 5);
			if (!result)
				print_error("ft_strdup failed");
			return (result);
		}
		i++;
	}
	return (NULL);
}

//this functions locates where the command is in our path
//and checks if we have the permissions to execute the command
char	*create_command(char *argv, char **env)//you have to free the command once used
{
	char	*path;
	char	**array;
	char	*command;
	char	**cmdarg;
	int		x;

	x = 0;
	path = get_path_from_env(env);
	array = ft_split_for_slash(path, ':');
	cmdarg = ft_split(argv, ' ');
	if (!path || !array || !cmdarg)
		print_error("failed creating the variables");
	while (array[x])
	{
		command = ft_strjoin(array[x], cmdarg[0]);//you test only the first command
		if (access(command, X_OK) == 0)
			return (free_array(array), free_array(cmdarg), free(path), command);
		free(command);
		x++;
	}
	return (free_array(array), free_array(cmdarg), free(path), NULL);
}

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

/*int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	char	**array_cmd;
	int		i;

	i = -1;
	cmd = create_command(argv[2], env);
	printf("cmd = %s\n", cmd);
	array_cmd = ft_split(argv[2], ' ');
	while (array_cmd[++i])
		printf("array_cmd[%i] = %s\n", i, array_cmd[i]); 
	execve(cmd, array_cmd, env);
	argc = 0;
	return (0);
}*/


//on veut une fonction qui sort du programme lorsque la str est strictement la meme que le LIMITER
//si la fonction renvoie 1 => on sort
//
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

/*int	main(int argc, char **argv)
{
	char	*line;

	line = get_next_line(0);
	printf("go_out_from_heredoc = %i\n", go_out_from_heredoc(line, argv[2]));
	argc = 0;
	printf("%s\n", argv[2]);
	printf("len_line = %i\n", (int)ft_strlen(line));
	printf("len_limiter = %i\n", (int)ft_strlen(argv[2]));
	return (0);
}*/

int	manage_infile_and_heredoc(char *infile)
{
	int	fd;

	if (!ft_strncmp(infile, "here_doc", 8))
	{
		return (1);
	}
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		print_error("open failed");
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	manage_here_doc(char **argv)
{
	char	*line;

	while (1)
	{
		write(2, "test", 4);
		line = get_next_line(0);
		if (!line)
			print_error("failed with GNL");
		if (go_out_from_heredoc(line, argv[2]))
		{
			break ;
		}
	}
	printf("we go out from the here_doc\n");
	return (0);
}

/*int	main(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5)
		print_error("please follow this instructions: \
				./pipex infile 'cmd1' 'cmd2' 'cmd..' outfile");
	i = 1;
	j = 1;
	if (manage_infile_and_heredoc(argv[1]) == 1)
	{
		manage_here_doc(argv);
		i++;
	}
	return (0);
}*/

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	j;

	if (argc < 5)
		print_error("please follow this instructions: \
				./pipex infile 'cmd1' 'cmd2' 'cmd..' outfile");
	i = 1;
	j = 1;
	if (manage_infile_and_heredoc(argv[1]) == 1)
	{
		manage_here_doc(argv);
		write(2, "simon", 5);
		i++;
	}
	while (++i < argc - 2)
		manage_command(argv[i], env);
	while (++j < argc - 3)
		wait(NULL);
	manage_outfile(argv[argc - 1], argv[i], env);
	return (0);
}
