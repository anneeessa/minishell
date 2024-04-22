/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:01:07 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:01:07 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i])
		return (1);
	else if (s2[i])
		return (1);
	else
		return (0);
}

// int main()
// {
// 	char	*s1 = "x12";
// 	char	*s2 = "x12";
// 	printf("%d", strcmp(s1, s2));
// 	printf("\n%d", ft_strcmp(s1, s2));
// }