/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:30:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/10 20:02:05 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <stdio.h>//perror
# include <sys/wait.h>//wait
# include <unistd.h>//dup, dup2, write, execve, access, pipe
# include <fcntl.h> //open, close
# include "get_next_line.h"

# define WRITE_END	1
# define READ_END	0

/*typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**env;
	char	**path;
	int		is_here_doc;
//the pipe
//the fd of infile
//the fd of outfile
}			t_pipex;
*/

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

//utils
char	**ft_split(const char *s, char c);
char	**free_array(char **array);
char	**ft_split_for_slash(const char *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
void	print_list(t_list *lst);

#endif
