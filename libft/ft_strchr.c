/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:41:55 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:31:25 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == (char)c)
			return ((char *)str + i);
	if (str[i] == (char)c)
		return ((char *)str + i);
	return (NULL);
}

/* int main()
{
	printf("%s", strchr("gatto", 97));
} */