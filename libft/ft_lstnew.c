/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:46:50 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:21:45 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/* int main()
{
    int num1 = 42;
    int num2 = 99;

    t_list *node1 = ft_lstnew(&num1);
    if (node1 == NULL) {
        printf("Memory allocation failed for node1\n");
        return 1;
    }
    t_list *node2 = ft_lstnew(&num2);
    if (node2 == NULL) {
        printf("Memory allocation failed for node2\n");
        return 1;
    }
    node1->next = node2;
    t_list *current = node1;
    while (current != NULL) {
        printf("Content: %d\n", *(int *)current->content);
        current = current->next;
    }
    free(node1);
    free(node2);

    return 0;
} */
