/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:46:05 by mfanelli          #+#    #+#             */
/*   Updated: 2024/11/27 11:37:07 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (str[++i])
	{
		if (str[i] == (char)c)
			temp = (char *)&str[i];
	}
	if (c == '\0')
		return ((char *)&str[i]);
	return (temp);
}

/* int main()
{
	printf("%s", strrchr("", '\0'));
} */