/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:17:00 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/13 15:27:45 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
//int	dup2(int oldfd, int newfd);
//int	dup2(int the_one_where_we_write, int the_current_one);

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

void	create_first_process();

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

/*int	main(int argc, char **argv)//, char **env)
{
	int		i;
//	char	*cmd;
//	char	**cmdarg;
	int		pid;
//	int		pip[2];
	int		infile;
	char	buffer[29];
	int		bytes_read;

	i = 1;
	while (argv[i] && i < argc - 1)
	{
//		if (pipe(pip) == -1)
//			print_error("pipe failed");
		pid = fork();//attention tu vas creer 2^n process
		if (pid == -1)
			print_error("fork failed");
		if (pid == 0)
		{
			//we want to read what's the infile
			//we want to execute the first command
			infile = open("infile", O_RDONLY);
			printf("infile = %i\n", infile);
			bytes_read = read(infile, buffer, sizeof(buffer));
			printf("bytes read = %i\n", bytes_read);
			printf("%s", buffer);

		}
		i++;
//		free(cmd);
		wait(NULL);
	}
//	close(pip[WRITE_END]);
//	close(pip[READ_END]);
	return (0);
}*/

/*int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	int		i;
	t_list	*new_node;
	t_list	*lst;

	lst = NULL;
	i = 1;
	while (argv[i] && i < argc - 1)
	{
		cmd = create_command(argv[i], env);
		new_node = ft_lstnew(cmd);
		if (!new_node)
			print_error("malloc failed");
		ft_lstadd_back(&lst, new_node);
		i++;
		free(cmd);
//		free(new_node);
	}
	print_list(lst);
	ft_lstclear(&lst);
	return (0);
}*/

//si l'infile n'existe pas, alors on n'execute pas la commande et on execute seulement la deuxieme commande, argv[2]
//dans tous les cas, il faudra creer l'outfile a la fin pour y mettre le resultat de la deuxieme commande
//si l'infile existe, on lit ce qu'il y a dans l'infile => on stock ce qu'on a lut dans un buffer
//on execute la premiere commande
//
//
//on veut garder le resultat de la premiere commande, independemmenent de l'infile 
//puis executer la deuxieme commande
//et mettre le resultat dans l'outfile
//how to execute the first command
//first we have to know which command it is
//know his command: for example if it's "ls", his location would be "/bin/ls"
//and execute it 
//then when we executed it, we want to write the result in the pipe
//we will read the pipe and execute the second command
//and we will write the output in the outfile

int	main(int argc char ** argv, char **env)
{
	int		i;
	char	*cmd;

	if (argc != 5)
		write(2, "we need 5 arguments\n", 20);
	i = 1;
	while (argv[i] && i < argc - 1)
	{
		cmd = create_command(argv[i], env);
		i++;
	}
	return (0);
}
