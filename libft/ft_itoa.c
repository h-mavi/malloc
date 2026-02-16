/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:21:24 by mfanelli          #+#    #+#             */
/*   Updated: 2026/02/16 14:44:05 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	n_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*int_min(char	*ptr)
{
	int		i;
	char	*int_min;

	i = -1;
	int_min = "-2147483648";
	while (int_min[++i] != '\0')
		ptr[i] = int_min[i];
	return (ptr);
}

static void	frite(char *ptr, int len, int ex)
{
	while (len--)
	{
		ptr[len] = ex % 10 + '0';
		ex /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		ex;

	ex = n;
	len = n_len(n);
	if (n < 0)
	{
		ex *= -1;
		len++;
	}
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (n == -2147483648)
		return (int_min(ptr));
	frite(ptr, len, ex);
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}

/* int	main(void)
{
	int	a = -623;
	int b = 0;
	int c = -2147483648;
	int d = 42;
	char	*aptr = ft_itoa(a);
	char	*bptr = ft_itoa(b);
	char	*cptr = ft_itoa(c);
	char	*dptr = ft_itoa(d);
	printf("-> %d | \"%s\"\n", a, aptr);
	printf("-> %d | \"%s\"\n", b, bptr);
	printf("-> %d | \"%s\"\n", c, cptr);
	printf("-> %d | \"%s\"\n", d, dptr);
	free(aptr);
	free (bptr);
	free (cptr);
	free (dptr);
} */