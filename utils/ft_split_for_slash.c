/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_slash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:30:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/03/19 20:09:59 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//this function is for the variable path in our main
//We want a function split that cuts all the path in several strings
//divided by ':'
//but we want to remove the 'PATH=' at the beginning
//AND at the end of each strings we want to add '/'
// => we will have to add + 1 to our malloc
//then the array/matrix ends with NULL

int	countwords(const char *s, char c);

//this is the same function as the split one but we add '+ 1' for the '/'
static char	**draw_array_for_slash(char **array, const char *s, char c)
{
	int		i;
	int		x;
	int		count;

	i = 0;
	count = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		if ((s[i] == c && count > 0) || (s[i] != c && s[i + 1] == '\0'))
		{
			array[x] = malloc((count + 1 + 1) * sizeof(char));
			if (!array[x])
				return (NULL);
			x++;
			count = 0;
		}
		i++;
	}
	return (array);
}

//We had previously added space for the '/'. Now we write it at the string's end
static char	**complete_array_for_slash(char **array, const char *s, char c)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (s[i])
	{
		if (s[i] != c)
			array[x][y++] = s[i];
		if ((s[i] == c && i > 0 && s[i - 1] != c)
			|| (s[i] != c && s[i + 1] == 0))
		{
			array[x][y] = '/';
			y++;
			array[x][y] = '\0';
			x++;
			y = 0;
		}
		i++;
	}
	return (array);
}

char	**ft_split_for_slash(const char *s, char c)
{
	char	**array;
	int		wc;

	wc = countwords(s, c);
	array = malloc((wc + 1) * sizeof(*array));
	if (!array)
		return (NULL);
	if (draw_array_for_slash(array, s, c))
	{
		complete_array_for_slash(array, s, c);
		array[wc] = NULL;
	}
	else
		array = free_array(array);
	return (array);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char	str[90] = "";
	char	**array;
	int		x;

	x = 0;
	array = ft_split(str, ' ');
	while (array[x])
	{
		printf("%s\n", array[x]);
		x++;
	}
	return (0);
}*/
