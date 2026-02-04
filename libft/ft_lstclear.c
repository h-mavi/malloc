/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:48:08 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/13 08:59:40 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ex;

	while (*lst)
	{
		ex = *lst;
		del((*lst)->content);
		*lst = (*lst)->next;
		free(ex);
	}
	*lst = NULL;
}
