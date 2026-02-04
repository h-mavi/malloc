/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:34:31 by mfanelli          #+#    #+#             */
/*   Updated: 2026/01/04 10:34:49 by mfanelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int a)
{
	if (ft_isalpha(a) || ft_isdigit(a))
		return (1);
	return (0);
}

/* int main() {
    char test_chars[] = {'a', '1', '#', 'Z', '9', ' ', '\0'};
    
    for (int i = 0; test_chars[i] != '\0'; i++) {
        char c = test_chars[i];
        printf("Character: %c\n", c);
        printf("ft_isalnum: %d\n", ft_isalnum(c));
        printf("\n");
    }
    return 0;
}
 */