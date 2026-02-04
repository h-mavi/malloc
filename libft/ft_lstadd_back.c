/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:47:46 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/05 14:40:33 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ex;

	ex = NULL;
	if (!new)
		return ;
	if (lst && lst[0])
	{
		ex = *lst;
		while (ex->next != NULL)
			ex = ex->next;
		ex->next = new;
	}
	else
		*lst = new;
	return ;
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
int main()
{
	t_list *new = ft_lstnew("ciao");
	t_list *sec = ft_lstnew("come");
	t_list *ter = ft_lstnew("va");

	print_list(new);
	printf("\n\n");

	ft_lstadd_back(&new, sec);
	
	print_list(new);
	printf("\n");
	
	ft_lstadd_back(&new, ter);
	
	print_list(new);
	printf("\n");
} */
