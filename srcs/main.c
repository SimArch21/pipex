/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:31:06 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/10 19:29:33 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <stdio.h>//WATCH OUT YOU USE A FORBIDDEN LIBRARY

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

int	print_error(char *msg)
{
	perror(msg);
	exit(1);
}

//we want to store all the name of PATH starting by the '/' in a variable 
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

char	*first_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 32)
		{
			str[i] = '\0';
			return (str);
		}
		i++;
	}
	return (str);
}

//this functions where the command is located in our path
//and if we have the permissions to execute the command
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

/*void	child_process(int f1, char *cmd1)
{
	dup2(f1, STDIN_FILENO);
	if (dup2 < 0)
		print_error("dup2 failed");
	dup2(fd[1], STDOUT_FILENO);
	if (dup2 < 0)
		print_error("dup2 failed");
	close(fd[0]);
	close(f1);
}*/

/*void	pipex(int f1, int f2, char **argv, char **env)
{
	pid_t	pid;
	int		fd[2];
	char	*cmd1;
	char	*cmd2;

	cmd1 = create_command(argv[2], env);
	cmd2 = create_command(argv[3], env);
	if (pipe(fd) == -1)
		print_error("pipe failed");
	pid = fork();
	if (pid < 0)
		print_error("fork failed");
	if (pid == 0)
	{
//		child_process(f1, cmd1);
		printf("process child f1 = %i et f2 = %i\n", f1, f2);
		write(1, "1\n", 2);
		wait(NULL);
	}
	else
	{
//		parent_process(f2, cmd2);
		printf("process parent f1 = %i et f2 = %i\n", f1, f2);
		write(1, "2\n", 2);
		wait(NULL);
	}
	free(cmd1);
	free(cmd2);
}
*/

/*void	pipex(int f1, int f2, char **argv, char **env)
{
	dup2(f1, STDIN_FILENO);
	
}*/

//READ_END 0
//WRITE_END 1
void	create_pipe(char **argv, char **env, int outfile)
{
	char	*path_with_cmd1;
	char	**cmdargs;
	pid_t	pid;
	int		fd[2];
	char	buffer[2048];

	path_with_cmd1 = create_command(argv[2], env);
	cmdargs = ft_split(argv[2], ' ');
	if (pipe(fd) == -1)
		print_error("pipe failed: ");
//	printf("pipe result: %i\n", pipe_result);
//	Fork a child process.
	pid = fork();
	dup2(outfile, STDOUT_FILENO);
//	printf("pid after fork: %i\n", pid);
//	execve(path_with_cmd1, cmdargs, env);//at the last moment you have to use execve otherwise your code won't run anymore.
//	printf("fork result: %i\n", pid);
	if (pid == 0)//child process: we read what's in the infile
	{
        close(fd[WRITE_END]);// Ferme l'extrémité d'écriture du tube dans le processus fils
		if (read(fd[0], buffer, ft_strlen(buffer)) == -1)
			print_error("read failed: ");
		close(fd[READ_END]);
//		close(fd[WRITE_END]);//fd[0]//on ecrit sur l'infile => si on peut 
//		dup2(outfile, STDOUT_FILENO);
//		execve(path_with_cmd1, cmdargs, env);//at the last moment you have to use execve otherwise your code won't run anymore.
//		close(fd[READ_END]);
	}
	else if (pid > 0)//parent process: we will write the result of the cmd1
	{
		close(fd[READ_END]);
		if (write(fd[WRITE_END], buffer, ft_strlen(buffer)) == -1)
			print_error("write failed: ");
		dup2(outfile, STDOUT_FILENO);
		execve(path_with_cmd1, cmdargs, env);//at the last moment you have to use execve otherwise your code won't run anymore.
		close(fd[WRITE_END]);
//		close(fd[READ_END]);
	}
	else
		print_error("fork failed: ");
}

//READ_END 0
//WRITE_END 1
/*void	create_pipe(char **argv, char **env, int outfile)
{
	char	*path_with_cmd1;
	char	**cmdargs;
	pid_t	pid;
	int		fd[2];

	path_with_cmd1 = create_command(argv[2], env);
	cmdargs = ft_split(argv[2], ' ');
	if (pipe(fd) == -1)
		print_error("pipe failed: ");
//	Fork a child process.
	pid = fork();

}*/

//void	child_process_one(int fd[1], char *cmd1)//the cmd1 is the argv[1] convertit avec le path + le slash + argv[1]
int	main(int argc, char **argv, char **env)
{
//	char	*path;//free it once used
//	int		execve_nb;
	ssize_t	infile;
	ssize_t	outfile;
//	char	**array_cmds;

//	write(1, "2\n", 2);
	if (argc != 5)
		print_error("Not well written");
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		return (-1);
//	write(1, "2\n", 2);
	create_pipe(argv, env, outfile);

	argc = 0;
//	argv[0][0] = 'a';
//	child_process_one(fd[1], ft_split(argv[1], ' '));
//	sub_path = command(argv, env);
//	execve_nb = execve(sub_path, argv, env);
//	printf("execve number: %i\n", execve_nb);

//	printf("%i, %s\n", argc, *argv);
	return (0);
}
