/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:35:13 by mfanelli          #+#    #+#             */
/*   Updated: 2024/11/27 18:15:58 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int a)
{
	if ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'))
		return (1);
	return (0);
}

/* int()
{
    char test_chars[] = {'a', '1', '#', 'Z', '9', ' ', '\0'};
    
    for (int i = 0; test_chars[i] != '\0'; i++) {
        char c = test_chars[i];
        printf("Character: %c\n", c);
        printf("ft_isalpha: %d\n", ft_isalpha(c));
        printf("\n");
    }
    return 0;
}
 */