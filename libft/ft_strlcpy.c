/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:01:43 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:01:43 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(src);
	if (size == 0)
		return (j);
	i = 0;
	while (src[i] != '\0' && (i + 1) < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

// int main()
// {
// 	char *src = "";
// 	char dst[20];
// 	printf("%zu", strlcpy(dst, src, 5));
// 	printf("\n%s", dst);
// 	printf("%zu", ft_strlcpy(dst, src, 5));
// 	printf("\n%s", dst);
// }