/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:01:30 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:01:30 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char		*new_str;
	size_t		i;
	size_t		j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		new_str[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*joined_str;
// 	int		len;

// 	if (!s1)
// 		return ((char *)s2);
// 	if (!s2)
// 		return ((char *)s1);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	joined_str = (char *)malloc((len + 1) * sizeof(char));
// 	if (!joined_str)
// 		return (0);
// 	ft_strlcpy(joined_str, s1, len + 1);
// 	ft_strlcat(joined_str, s2, len + 1);
// 	return (joined_str);
// }

// int main()
// {

// 	char *s2 = "Hello";
// 	char *s1 = NULL;

// 	printf("%s", ft_strjoin(s1, s2));
// }