/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:38:21 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/17 19:47:21 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//Small examples to understand the access function
//int access(const char *path, int FLAG);
/*int main(void)
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

//Small examples to understand the dup2 function
//int dup2(int oldfd, int newfd);
/*int	main(void)
{
	int	fd;

	write(1, "marta\n", 6);
	dup2(1, 10);
	write(10, "my name is simon\n", 17);
	fd = open("infile", O_RDWR); 
	if (fd == -1)
		perror("open failed, dup2 not executed");
	dup2(fd, 10);
	write(10, "this is a test\n", 15);
	return (0);
}*/

//Small examples to understand the execve function
//int	execve(const char *path_cmd, char const **array_cmd, char const **env);
/*int	main(int argc, char **argv, char **env)
{
	char	**array_cmd;

	if (argc > 0)
	{
		array_cmd = ft_split(argv[1], ' ');
		execve("/bin/ls", array_cmd, env);
		write(1, "simon", 5);//it doesn't print
	}
	return (0);
}*/

/*int	main(void)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 5)
	{
		line = get_next_line(0);
		write(1, line, ft_strlen(line));
		free(line);
		i++;
	}
	return (0);
}*/

/*int	main(void)
{
	int	fd;

	fd = open("infile", O_RDONLY);
	if (fd == -1)
		perror("open failed");
	return (0);
}*/

//Small examples to understand the fork function
//pid_t	fork(void);
/*int	main(void)
{
	int	pid;

//	wait(NULL);
	pid = fork();
	if (pid == 0)
		write(1, "hijo\n", 5);
	else if (pid > 0)
	{
		wait(NULL);
		write(1, "padre\n", 6);
	}
	return (0);
}*/

//Small examples to understand the pipe function
//int	pipe(int fildes[2]);
/*int	main(void)
{
	int	fildes[2];
	int	tube;
	char	buffer[256];

//	fildes[0] = READ_END;
//	fildes[1] = WRITE_END;
	tube = pipe(fildes);
	printf("tube = %i\n", tube);
	printf("fildes[0] = %i\n", fildes[0]);
	printf("fildes[1] = %i\n", fildes[1]);
	write(fildes[1], "marta\n", 6);
	read(fildes[0], buffer, sizeof(buffer));
	printf("buffer = %s\n", buffer);
	close(fildes[0]);
	close(fildes[1]);
	return (0);
}*/


//we want know why we choose STDOUT_FILENO
//and if we can read after closing the WRITE_END => we can thanks to the READ_END
//yes we can dice marta even after it's closed
/*int	main(void)
{
	int	pipe_fd[2];
	char	buffer[256];

	if (pipe(pipe_fd) == -1)
		perror("pipe failed");

//	close(pipe_fd[READ_END]);
	dup2(pipe_fd[WRITE_END], 10);//WHY DID YOU CHOOSE THE STDOUT_FILENO
	close(pipe_fd[WRITE_END]);

	write(10, "hola", 4);
	if (read(pipe_fd[READ_END], buffer, sizeof(buffer)) <= 0)
		perror("read failed");
	write(2, buffer, ft_strlen(buffer));
	close(pipe_fd[READ_END]);
	return (0);
}*/

/*int	main(int argc, char **argv, char **env)
{
	int		pid;
	char	**array_cmd_ls;
	char	**array_cmd_pwd;

	array_cmd_ls = ft_split(argv[1], ' ');
	array_cmd_pwd = ft_split(argv[2], ' ');
	pid = fork();
	if (pid < 0)
		perror("fork failed");
	if (pid == 0)
	{
		execve("/bin/ls", array_cmd_ls, env);
	}
	else
	{
		execve("/bon/pwd", array_cmd_pwd, env);
	}
	argc = 0;
	return (0);
}*/
