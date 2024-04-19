/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:15:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/19 15:58:35 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	go_out_from_heredoc(char *line, char *heredoc_limiter)
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

void	get_lines_from_heredoc(char *limiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (go_out_from_heredoc(line, limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[WRITE_END]);
		free(line);
	}
	close(pipe_fd[WRITE_END]);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(pipe_fd[READ_END]);
}
