/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:14:28 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/11 20:37:43 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	write_msg(const char *msg)
{
	if (write(1, &msg, ft_strlen(msg)) == -1)
		write(1, "write failed\n", 13);
}

int	main(void)
{
	int		infile;
	char	buffer[256];
	int		bytes_read;

	infile = open("infile", O_RDONLY);
	printf("infile = %i\n", infile);
	bytes_read = read(infile, buffer, sizeof(buffer));
	printf("bytes read = %i\n", bytes_read);
	printf("%s", buffer);
	return (0);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int infile;
    char buffer[256];
    ssize_t bytes_read;

    // Ouvrir le fichier en mode lecture seule
    infile = open("../infile", O_RDONLY);
    if (infile == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("infile = %i\n", infile);

    // Lire à partir du fichier
    bytes_read = read(infile, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        close(infile); // Fermer le descripteur de fichier avant de quitter
        exit(EXIT_FAILURE);
    }
    printf("bytes read = %zd\n", bytes_read);

    // Afficher les données lues
    printf("%.*s", (int)bytes_read, buffer);

    // Fermer le descripteur de fichier
    close(infile);

    return 0;
}*/


/*int	main(void)
{
	char	buffer[256];

	printf("%lu\n", sizeof(buffer));
	return (0);
}*/

/*int	main(void)
{
	int	fd;

	fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("fd = %i\n", fd);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (1);
	printf("this is dup2 function\n");
	close(STDOUT_FILENO);
	close(fd);
	return (0);
}*/
