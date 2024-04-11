/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:42:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/10 23:11:34 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//t_list	*ft_lstnew(void *content);
//void	ft_lstadd_back(t_list **lst, t_list *new);
//void	ft_lstclear(t_list **lst);
//void	print_list(t_list *lst);

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;
//	char	*str;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
//	str = ft_strdup(content);
	lst->content = ft_strdup(content);
	lst->next = NULL;
//	free(str);
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
		tmp = NULL;
	}
	lst = NULL;
}

/*t_list	*create_list(int argc, char **argv)
{
	t_list			*lst;
	void			content;
	t_list			*new_node;

	i = 1;
	lst = NULL;
	while (i < argc)
	{
		content = (argv[i]);
		new_node = ft_lstnew(content);
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&lst, new_node);
		i++;
	}
	return (lst);
}*/

void print_list(t_list *lst)
{
	int	i;

	i = 0;
    while (lst != NULL)
	{
		if (lst)
		{
			printf("---------------------------\n");
			printf("node[%i]  = %p\n", i, &lst->content);
			printf("         = %s\n", lst->content);
			lst = lst->next;
			i++;
		}
    }
}
