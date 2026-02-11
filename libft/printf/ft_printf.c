/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:03:14 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/23 12:20:22 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(va_list args, const char *format, int i)
{
	if (format[i + 1] == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format[i + 1] == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format[i + 1] == '%')
		return (ft_putchar('%'));
	else if (format[i + 1] == 'i' || format[i + 1] == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (format[i + 1] == 'u')
		return (ft_unsigned_putnbr(va_arg(args, unsigned int)));
	else if (format[i + 1] == 'x' || format[i + 1] == 'X')
		return (ft_putnbrhex(va_arg(args, int), format[i + 1]));
	else if (format[i + 1] == 'p')
		return (ft_putptr((unsigned long)va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (format == NULL)
		return (-1);
	va_start (args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if ((format[i] == '%' && format[i + 1] != '\0'))
		{
			len += ft_check(args, format, i);
			i += 2;
		}
		else if (format[i] != '%')
			len += ft_putchar(format[i++]);
	}
	va_end (args);
	return (len);
}

/* int	main(void)
{
	int o, c, i;

	o = printf("OG -> origin-\n");
	c = ft_printf("RE -> replic-\n");
	printf("OG len -> %d | CAP len -> %d\n", o, c);

	printf("----------------------Characters----------------------\n");
	o = printf("OG -> %c\n", 'a');
	c = ft_printf("RE -> %c\n", 'a');
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %c\n", 'A');
	c = ft_printf("RE -> %c\n", 'A');
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	printf("----------------------Numbers----------------------\n");
	o = printf("OG -> %d\n", 42);
	c = ft_printf("RE -> %d\n", 42);
	printf("OG len -> %d | RE len -> %d\n", o, c);

	o = printf("OG -> %d\n", 0);
	c = ft_printf("RE -> %d\n", 0);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %d\n", -42);
	c = ft_printf("RE -> %d\n", -42);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %d\n", 2147483647);
	c = ft_printf("RE -> %d\n", 2147483647);
	printf("OG len -> %d | RE len -> %d\n", o, c);

	c = ft_printf("# only RE -> %d\n", -2147483648);
	
	c = ft_printf("# only RE -> %d\n", 2147483648);
	
	printf("----------------------Strings----------------------\n");
	o = printf("OG -> %s\n", "Hello World!");
	c = ft_printf("RE -> %s\n", "Hello World!");
	printf("OG len -> %d | RE len -> %d\n", o, c);

	o = printf("OG -> %s\n", "");
	c = ft_printf("RE -> %s\n", "");
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	printf("----------------------Percent----------------------\n");
	o = printf("OG -> %%\n");
	c = ft_printf("RE -> %%\n");
	printf("OG len -> %d | RE len -> %d\n", o, c);

	printf("----------------------Unsigned N.----------------------\n");
	o = printf("OG -> %u\n", 42);
	c = ft_printf("RE -> %u\n", 42);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %u\n", 0);
	c = ft_printf("RE -> %u\n", 0);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %u\n", -42);
	c = ft_printf("RE -> %u\n", -42);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	c = ft_printf("# only RE -> %u\n", 4294967295);
	
	c = ft_printf("# only RE -> %u\n", 4294967296);
	
	printf("----------------------Hexadecimal----------------------\n");
	o = printf("OG -> %x\n", 42);
	c = ft_printf("RE -> %x\n", 42);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %x\n", 0);
	c = ft_printf("RE -> %x\n", 0);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %x\n", -42);
	c = ft_printf("RE -> %x\n", -42);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %x\n", 2147483647);
	c = ft_printf("RE -> %x\n", 2147483647);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %X\n", 42);
	c = ft_printf("RE -> %X\n", 42);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %X\n", 0);
	c = ft_printf("RE -> %X\n", 0);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %X\n", -42);
	c = ft_printf("RE -> %X\n", -42);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %X\n", 2147483647);
	c = ft_printf("RE -> %X\n", 2147483647);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	c = ft_printf("# only RE -> %x\n", -2147483648);
	
	c = ft_printf("# only RE -> %X\n", -2147483648);
	
	printf("----------------------Addresses----------------------\n");
	o = printf("OG -> %p\n", &o);
	c = ft_printf("RE -> %p\n", &o);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
	o = printf("OG -> %p\n", &i);
	c = ft_printf("RE -> %p\n", &i);
	printf("OG len -> %d | RE len -> %d\n", o, c);
	
} */
