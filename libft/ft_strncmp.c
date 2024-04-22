/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:02:01 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:02:01 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int main()
// {
// 	char	*s1 = "\x12\xff\x65\x12\xbd\xde\xad";
// 	char	*s2 = "\x12\x02";
// 	size_t	size = 6;
// 	printf("%d", strncmp(s1, s2, size));
// 	printf("\n%d", ft_strncmp(s1, s2, size));
// }