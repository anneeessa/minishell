/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:57:37 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 18:57:37 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb >= 65535 && size >= 65535)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (0);
	ft_bzero(result, (nmemb * size));
	return (result);
}

// int main(void)
// {
// 	//size_t size = 0;
// 	printf("%s", calloc(0, 0));
// 	printf("\n%s", ft_calloc(0, 0));
// }