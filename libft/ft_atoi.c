/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:31:34 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 14:16:30 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] >= 1 && nptr[i] <= 32) || nptr[i] == 127)
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && ft_isdigit(nptr[i]))
		num = (num * 10) + (nptr[i++] - '0');
	num = num * sign;
	return (num);
}

/* int main(void)
{
	char *test_cases[] = {
		"42",
		"-42",
		"  42",
		"  \t  42",
		"  -1234",
		"+1234",
		"0",
		"-0",
		"  \t +123abc",
		"abc123",
		"  +2147483647",
		"  -2147483648", 
		"  99999999999999", 
		NULL
	};

	
	for (int i = 0; test_cases[i] != NULL; i++) {
		int result = ft_atoi(test_cases[i]);
		int res = atoi(test_cases[i]);
		printf("Input: \"%s\", ft_atoi: %d  %d\n", test_cases[i], result, res);
	}
} */