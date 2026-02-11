/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:40:42 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/13 09:24:20 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_putnbr(unsigned long n)
{
	int		i;
	int		temp;
	char	num[11];

	i = 0;
	while (n >= 10)
	{
		num[i++] = (n % 10) + '0';
		n = n / 10;
	}
	num[i] = (n % 10) + '0';
	temp = i + 1;
	while (i >= 0)
		write(1, &num[i--], 1);
	return (temp);
}

int	ft_putnbrhex(unsigned int n, char c)
{
	int		j;
	int		len;
	int		ris[9];
	char	*hex;

	j = 0;
	if (c == 'x')
		hex = "0123456789abcdef";
	else if (c == 'X')
		hex = "0123456789ABCDEF";
	if (n == 0)
		return (write(1, "0", 1));
	ris[j++] = '\0';
	while (n != 0 && hex[0] != '\0' && n > 0)
	{
		ris[j++] = hex[n % 16];
		n /= 16;
	}
	len = j - 1;
	j -= 1;
	while (ris[j])
		write(1, &ris[j--], 1);
	return (len);
}

int	limit(int n)
{
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	else if (n == 0)
		return (write (1, "0", 1));
	return (0);
}

int	ft_putnbr(int n)
{
	int		i;
	int		temp;
	char	num[11];

	i = 0;
	temp = 0;
	if (n == 0 || n <= INT_MIN)
		return (limit(n));
	if (n < 0)
	{
		n = -n;
		temp += write(1, "-", 1);
	}
	while (n >= 10)
	{
		num[i++] = (n % 10) + '0';
		n = n / 10;
	}
	num[i] = (n % 10) + '0';
	temp += i + 1;
	while (i >= 0)
		write(1, &num[i--], 1);
	return (temp);
}
