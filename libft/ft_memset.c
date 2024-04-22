/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:00:12 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:00:12 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = (unsigned char)c;
	return (s);
}
// int main()
// {

// 	char st[50];
// 	char str[50];

// 	memset(st, '$', 10);
// 	printf("%s", st);
// 	ft_memset(str, '$', 10);
// 	printf("\n%s", str);
// 	return (0);
// }