/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:39:46 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/06 17:34:18 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_rev_int_tab_ptr(int *tab, int size)
{
	int	count;
	int	c;

	count = 0;
	while (count < size / 2)
	{
		c = tab[count];
		tab[count] = tab[size - 1 - count];
		tab[size - 1 - count] = c;
		count++;
	}
	tab[size] = '\0';
	count = 0;
	while (tab[count])
		write(1, &tab[count++], 1);
	return ;
}

int	ft_putnbrhex_ptr(unsigned long nbr)
{
	int					j;
	int					ris[20];
	unsigned long long	ex;
	char				*hex;

	j = 0;
	ex = nbr;
	hex = "0123456789abcdef";
	if (ex == 0)
		write(1, "0", 1);
	while (ex != 0 && hex[0] != '\0' && ex > 0)
	{
		ris[j++] = hex[ex % 16];
		ex /= 16;
	}
	ft_rev_int_tab_ptr(ris, j);
	return (j);
}

int	ft_putptr(unsigned long long ptr)
{
	int	len;

	if (!ptr)
		return (write (1, "(nil)", 5));
	len = 0;
	write(1, "0x", 2);
	len += 2;
	len += ft_putnbrhex_ptr((unsigned long)ptr);
	return (len);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (write (1, "(null)", 6), 6);
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	ft_putchar(char c)
{
	return (write (1, &c, 1));
}
