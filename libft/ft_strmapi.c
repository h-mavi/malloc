/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:44:49 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 12:31:59 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*ptr;

	if (!s || !f)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (++i < len && s[i] != '\0')
		ptr[i] = f(i, s[i]);
	ptr[i] = '\0';
	return (ptr);
}

/* static char	to_Upper(unsigned int index, char c) 
{
    if (index % 2 == 0)
        return (char)(c - 32);
    return c;
}

int main(void)
{
    char	a[] = "pippo baudo";
	char	*ptr;
	ptr = ft_strmapi(a, to_Upper);
	printf("%s", ptr);
    free(ptr);
} */
