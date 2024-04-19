/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:26:09 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/16 12:51:28 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>


//tests to understand the dup2 function
int	main(void)
{
	write(1, "hola simon\n", 11);
//	close(1);
	dup2(1, 90);
	close(1);
	write(1, "hola simon\n", 11);
	write(90, "hola simon2\n", 12);
	write(1, "hola simon\n", 11);
	//dup2(90, 1);
	//write(90, "hola simon2\n", 12);
	//write(1, "hola simon\n", 11);
	return (0);
}
