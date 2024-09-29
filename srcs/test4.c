/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:38:21 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/29 13:09:13 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include <stdio.h>

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
	close(1);
	write(1, "1 is closed\n", 12);
	write(10, "10 is still open\n", 17);//msg visible in the std_out
	fd = open("infile", O_RDWR);
	if (fd == -1)
		perror("open failed, dup2 not executed");
	dup2(fd, 10);//now 10 will write in fd only
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
//	fildes[0] = READ_END;
//	fildes[1] = WRITE_END;
//int	pipe(int fildes[2]);
/*int	main(void)
{
	int	fildes[2];
	int	tube;
	char	buffer[256];

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
