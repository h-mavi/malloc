/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:33:23 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:20:56 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (i < n)
		str[i++] = 0;
	return (s);
}
/* int main()
{
    char buffer[10] = "123456789";
    printf("Prima di ft_bzero: \"%s\"\n", buffer);

    ft_bzero(buffer, 5);
    printf("Dopo ft_bzero (5 byte): \"%s\" -> \"%s\"\n", buffer, buffer + 5);

    char buffer2[10] = "abcdefghi";
    printf("Prima di bzero (standard): \"%s\"\n", buffer2);
    bzero(buffer2, 5);
    printf("Dopo bzero (5 byte): \"%s\" -> \"%s\"\n", buffer2, buffer2 + 5);
} */