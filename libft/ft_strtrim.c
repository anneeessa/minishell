/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:02:20 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:02:20 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	char	*start_str;
	char	*end_str;

	if (!s1)
		return (0);
	start_str = (char *)s1;
	end_str = start_str + ft_strlen(s1);
	while (*start_str != 0 && ft_strchr(set, *start_str))
		start_str++;
	while ((start_str < end_str) && ft_strchr(set, *(end_str - 1)))
		end_str--;
	result = ft_substr(start_str, 0, end_str - start_str);
	return (result);
}

// int main()
// {
// 	char *s1 = "Helolo";
// 	char *set = "olo";
// 	printf("%s\n", ft_strtrim(s1, set));
// }