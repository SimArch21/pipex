/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:02:01 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/30 11:14:22 by simarcha         ###   ########.fr       */
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
	write(10, "my name is simon\n", 17);//msg visible in the std_out
	close(1);
	write(1, "1 is closed\n", 12);//msg NOT visible in the std_out
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
	write(1, "wait\n", 5);
	pid = fork();
	if (pid == 0)
	{
		//sleep(1);
		write(1, "hijo\n", 5);
	}
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

//Small examples to understand the wait function
//pid_t wait(int *status);
//pid_t waitpid(pid_t pid, int *status, int options);
/*int	main(void)
{
	int pid;
	int status;

	printf("Parent: %d\n", getpid());
	pid = fork();
	printf("pid = %d\n", pid);//two processes are entering in this line => 2 prints
	if (pid == 0)
	{
		printf("Child %d\n", getpid());
		sleep(2);
		exit(EXIT_SUCCESS);
	}

//Comment from here to...
	//Parent waits process pid (child)
	wait(&status);
	printf("status = %i\n", status);
	waitpid(pid, &status, 0);//these 2 lines are waiting for the exact same pid
	//with the second one, you will have more data about the status, for signal for example
	printf("status = %i\n", status);
	
	//Option is 0 since I check it later
	if (WIFSIGNALED(status))
		printf("Error\n");
	else if (WEXITSTATUS(status))
		printf("Exited Normally\n");
//To Here and see the difference
	printf("Parent: %d\n", getpid());

	return (0);
}*/