/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:33:49 by mfanelli          #+#    #+#             */
/*   Updated: 2026/02/16 14:43:58 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (nmemb >= SIZE_MAX || size >= SIZE_MAX || \
		((int)nmemb < 0 && size != 0) || ((int)size < 0 && nmemb != 0))
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, size * nmemb);
	return (str);
}

/* int main()
{
	if (ft_calloc(-5, -5) == NULL)
		printf("oke\n");
	else
		printf("nope\n");

    return 0;
} */