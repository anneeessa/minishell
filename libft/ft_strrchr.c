/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:02:14 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:02:14 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (c > 255)
		c = c - 256;
	i = ft_strlen(s);
	if (s[i] == c)
		return ((char *)(s + i));
	while (i--)
	{
		if (s[i] == c)
			return ((char *)(s + i));
	}
	return (0);
}

// int main()
// {
// 	char *s = "Hello World";
// 	char c = '\0';
// 	printf("%s", strrchr(s, c));
// 	printf("\n%s", ft_strrchr(s, c));
// }