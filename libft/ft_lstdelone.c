/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:47:57 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/05 15:14:08 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

/* void print_list(t_list *lst)
{
    while (lst->next != NULL)
    {
        printf("content -> %s", (char *)lst->content);
		printf("\n");
		printf("next -> %p", lst->next);
		printf("\n");
        lst = lst->next;
    }
	printf("content -> %s", (char *)lst->content);
	printf("\n");
	printf("next -> %p", lst->next);
	printf("\n");
}

void	del(t_list *node)
{
	free(node);
}

int main()
{
	t_list *new = ft_lstnew("ciao");
	t_list *sec = ft_lstnew("come");
	t_list *ter = ft_lstnew("va");

	print_list(new);
	printf("\n\n");

	ft_lstadd_back(&new, sec);
	ft_lstadd_back(&new, ter);
	
	print_list(new);
	printf("\n");

	ft_lstdelone(sec, &del);
	
	print_list(new);
	printf("\n\n");
	
	free(new);
	free(ter);
} */