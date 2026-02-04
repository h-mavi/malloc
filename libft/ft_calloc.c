/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:33:49 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/13 08:59:26 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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