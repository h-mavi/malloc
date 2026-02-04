/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:38:36 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 11:37:30 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	i = len;
	if (dst > src)
		while (--i >= 0)
			((char *)dst)[i] = ((char *)src)[i];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

/* int main()
{
	char wer[6] = "catto";
	char ter[6] = "catto";

	printf("%s\n", (char *)memmove(wer, wer + 1, 5));
	printf("%s\n", (char *)ft_memmove(ter, ter + 1, 5));
} */