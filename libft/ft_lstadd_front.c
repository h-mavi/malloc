/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:47:03 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:21:23 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/* int main(void)
{
	t_list *head = NULL;
	int a = 10;

	t_list *new_node = malloc(sizeof(t_list));
	new_node->content = &a;
	new_node->next = NULL;
	ft_lstadd_front(&head, new_node);
	printf("%d -> NULL\n", *(int *)head->content);
	free(new_node);
	return 0;
} */
