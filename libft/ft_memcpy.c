/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:00:00 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:00:00 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
	unsigned int	i;
	int				dest_len;

	if (dest == NULL && src == NULL )
		return (0);
	dest_len = 0;
	if (!dest)
		dest_len = ft_strlen(dest);
	i = 0;
	while (n--)
	{
		((unsigned char *)dest)[dest_len + i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// int main()
// {
// 	char str1[50] = "GeeksHello";
// 	char str2[50] = "GeeksFor";
// 	// memcpy(str1 + 5, str1, 9);
// 	// printf("%s", str1);
// 	printf("%s", str1);
// 	ft_memcpy(str2 + 5, str1, 8);
// 	printf("\n%s", str2);
// }