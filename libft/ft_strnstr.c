/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:02:08 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:02:08 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				j;
	int				s2_len;

	i = 0;
	j = 0;
	if (!s1 && n == 0)
		return (0);
	s2_len = ft_strlen(s2);
	if (s2_len == 0)
		return ((char *)(s1));
	while (s1[i] != '\0' && i < n)
	{
		if (s1[i] == s2[0])
		{
			while (s2[j] != '\0' && s1[i + j] == s2[j] && ((i + j) < n))
			{
				if (s2[j + 1] == '\0')
					return ((char *)(s1 + i));
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	char *s1 = "loxlhelw";
// 	char *s2 = "xl";
// 	// char *result;
// 	printf("%s", ft_strnstr(s1, s2, 6));
// }
