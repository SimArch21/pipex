/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:40:38 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/10 13:24:11 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	print_error(char *msg)
{
	perror(msg);
	exit(1);
}

//this function stores all the name of PATH starting by the '/' in a variable 
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

//this functions checks where the command is located in our path
//and checks if we have the permissions to execute the command
char	*create_command(char *argv, char **env)//you have to free the command once used
{
	char	*path;
	char	**array;
	char	*result;
	char	**cmdargs;
	int		x;

	x = 0;
	path = get_path_from_env(env);
	array = ft_split_for_slash(path, ':');
	cmdargs = ft_split(argv, ' ');
	if (!path || !array || !cmdargs)
		print_error("failed creating the variables");
	while (array[x])
	{
		result = ft_strjoin(array[x], cmdargs[0]);//you test only the first command
		if (!result)
			print_error("strjoin failed");
		if (access(result, X_OK) == 0)
			return (free_array(array), free_array(cmdargs), free(path), result);
		free(result);
		x++;
	}
	return (free_array(array), free_array(cmdargs), free(path), NULL);
}

void	first_subprocess(int fds[2], char *infile, char *cmd, char **env)
{
	int		pid;
	int		fd;
	char	*cmd_with_path;

	cmd_with_path = create_command(cmd, env);
	if (!cmd_with_path)
		print_error("command not found");
	pid = fork();
	if (pid == -1)
		print_error("fork failed");
	if (pid == 0)
	{
		close(fds[READ_END]);
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			print_error("open failed");
		dup2(fd, STDIN_FILENO);
		dup2(fds[WRITE_END], STDOUT_FILENO);
		if (execve(cmd_with_path, ft_split(cmd, ' '), env) == -1)
			print_error("execve failed");
	}
}

void	second_subprocess(int fds[2], char *outfile, char *cmd, char **env)
{
	int		pid;
	int		fd;
	char	*cmd_with_path;

	cmd_with_path = create_command(cmd, env);
	if (!cmd_with_path)
		print_error("cmd not found");

}

int	main(int argc, char **argv, char **env)
{
	int	fds[2];

	if (argc != 5)
		print_error("we want 5 arguments");
	if (pipe(fds) == -1)
		print_error("pipe error");
	first_subprocess(fds, argv[1], argv[2], env);
	wait(NULL);
	second_subprocess(fds, argv[4], argv[3], env);
	close(fds[READ_END]);
	close(fds[WRITE_END]);
	return (0);
}
