/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:57:30 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 18:57:30 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (n--)
	{
		((unsigned char *)s)[i++] = '\0';
	}
}

// int main()
// {

// 	char str[50] = "Hello world";
// 	// bzero(str, 4);
// 	ft_bzero(&str, 4);
// 	printf("%s", str);
// }