/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:47:30 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:21:29 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ex;

	ex = lst;
	if (!lst)
		return (lst);
	while (ex->next != NULL)
		ex = ex->next;
	return (ex);
}

/* t_list *create_node(void *content)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return NULL;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

int main(void)
{
    t_list *head = NULL;
    int a = 10, b = 20, c = 30;

    t_list *node1 = create_node(&a);
    t_list *node2 = create_node(&b);
    t_list *node3 = create_node(&c);

    node1->next = node2;
    node2->next = node3;
    head = node1;
    t_list *last = ft_lstlast(head);

	if(last == NULL)
	{
		printf("Head e' vuoto");
		return 0;
	}
    printf("Il contenuto dell'ultimo nodo è: %p\n", last->content);

    free(node1);
    free(node2);
    free(node3);

    return 0;
} */