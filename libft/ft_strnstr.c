/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:45:40 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 13:58:53 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*haystack;
	size_t	letters_left;
	size_t	little_len;

	if (little[0] == '\0')
		return ((char *)big);
	haystack = (char *)big;
	letters_left = len;
	little_len = ft_strlen(little);
	while (*haystack && letters_left-- >= little_len)
	{
		if (*haystack == *little)
			if (ft_strncmp((char *)little, haystack, little_len) == 0)
				return (haystack);
		haystack++;
	}
	return (NULL);
}
/* int main    ()
{
	printf("%s\n", ft_strnstr("come va", "", 11));
} */
	/* if (!hay || !needle)
		return (NULL); */