/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:43:21 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 12:00:37 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * len_s1 + len_s2 + 1);
	if (!str)
		return (NULL);
	str[len_s1 + len_s2] = '\0';
	while (--len_s2 >= 0)
		str[len_s1 + len_s2] = s2[len_s2];
	while (--len_s1 >= 0)
		str[len_s1] = s1[len_s1];
	return (str);
}

/* int main()
{
	printf("%s", ft_strjoin("NULL", "NULL"));
} */