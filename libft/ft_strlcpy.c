/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:44:00 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:22:40 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (!src)
		return (0);
	if (size < 1 || !dest)
		return (ft_strlen(src));
	i = -1;
	while (src[++i] != '\0' && i < size - 1)
		dest[i] = src[i];
	dest[i] = '\0';
	return (ft_strlen(src));
}

/* int	main(void)
{
	char	dest[70] = "cane e gatto";
	char	src[] = "07306802";
	int		count;

	count = ft_strlcpy(dest, src, 0);
	printf("%s\n", dest);
	printf("%s\n", src);
	printf("%d\n", count);
} */