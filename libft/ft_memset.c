/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:39:12 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:22:04 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buffer, int c, size_t count)
{
	char	*str;
	size_t	i;

	if (!buffer)
		return (NULL);
	str = (char *)buffer;
	i = 0;
	while (i < count)
		str[i++] = (unsigned char)c;
	return (buffer);
}
