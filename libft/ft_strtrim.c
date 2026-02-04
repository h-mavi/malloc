/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:10:15 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:10:06 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		y;
	int		x;
	char	*ptr;

	y = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[y]))
		y++;
	x = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[x]))
		x--;
	ptr = ft_substr(s1, y, (x - y) + 1);
	return (ptr);
}

/* int	main(void)
{
	char	a[] = "cia' cia'";
	char	*b = "'";
	char	*ptr = ft_strtrim(a, b);
	printf("%s", ptr);
	free(ptr);
} */
