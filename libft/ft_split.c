/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:13:51 by mfanelli          #+#    #+#             */
/*   Updated: 2026/02/16 14:44:31 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	len_arr_split(char const *arr, char c)
{
	int	i;
	int	x;

	i = 0;
	x = -1;
	while (arr[++x] != '\0')
		if ((arr[x] == c && arr[x + 1] != c && arr[x + 1] != '\0') || \
		(x == 0 && arr[x] != c))
			i++;
	return (i);
}

static void	frite(char *dest, int i, int conta, char const *s)
{
	int	g;

	g = -1;
	while (++g + i < i + conta)
		dest[g] = s[i + g];
	dest[g] = '\0';
}

static char	**fill(char **dest, char c, char const *s, int len_arr)
{
	int	i;
	int	x;
	int	y;
	int	conta;

	i = 0;
	x = 0;
	y = 0;
	while (x < len_arr)
	{
		conta = 1;
		while (s[i++] == c)
			;
		y = i;
		while (s[y] != '\0' && s[y++] != c)
			conta++;
		dest[x] = (char *) malloc(sizeof(char) * (conta + 1));
		if (!dest[x])
			return (NULL);
		frite(dest[x++], i - 1, conta, s);
		while (s[y] != '\0' && s[i++] != c)
			;
	}
	dest[x] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		x;
	int		len_arr;
	char	**dest;

	x = 0;
	len_arr = len_arr_split(s, c);
	dest = (char **) malloc(sizeof(char *) * (len_arr + 1));
	if (!dest)
		return (NULL);
	if (!fill(dest, c, s, len_arr))
	{
		while (x ++ <= len_arr)
			free(dest[x]);
		return (NULL);
	}
	return (dest);
}

/* int	main(void)
{
	char	a[] = "lanonna cari ola";
	char	**ptr;
	ptr = ft_split(a, ' ');
	printf("%s\n", ptr[0]);
	printf("%s\n", ptr[1]);
	printf("%s", ptr[2]);
	free(ptr[0]);
	free(ptr[1]);
	free(ptr[2]);
	free(ptr);
} */