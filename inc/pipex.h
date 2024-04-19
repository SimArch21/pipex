/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:30:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/19 20:19:04 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>//perror
# include <sys/wait.h>//wait
# include <unistd.h>//dup, dup2, write, execve, access, pipe
# include <fcntl.h> //open, close
# include "get_next_line.h"
# include "../utils/ft_printf/ft_printf.h"

# define WRITE_END	1
# define READ_END	0

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

//utils
char	**ft_split(const char *s, char c);
char	**free_array(char **array);
char	**ft_split_for_slash(const char *s, char c);

//libft_functions.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);

//create_command.c
int		print_error(char *msg);
char	*get_path_from_env(char **env);
char	*create_command(char *argv, char **env);

//manage_heredoc.c
void	get_lines_from_heredoc(char *limiter);

#endif
