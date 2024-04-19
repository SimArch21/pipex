/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:23:39 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/19 15:20:07 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	print_error(char *str)
{
	perror(str);
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
char	*create_command(char *argv, char **env)//you have to free once used
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
		command = ft_strjoin(array[x], cmdarg[0]);
		if (access(command, X_OK) == 0)
			return (free_array(array), free_array(cmdarg), free(path), command);
		free(command);
		x++;
	}
	return (free_array(array), free_array(cmdarg), free(path), NULL);
}
