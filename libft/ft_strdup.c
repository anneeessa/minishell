/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:01:13 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:01:13 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		s_len;
	int		i;

	i = -1;
	if (!s)
		return (malloc(sizeof(char)));
	s_len = ft_strlen(s);
	new_str = NULL;
	new_str = (char *)malloc((s_len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	new_str[s_len] = '\0';
	while (s[++i])
		new_str[i] = s[i];
	return (new_str);
}

// int main()
// {
// 	char *str = "helo world ";
// 	printf("%s", strdup(str));
// 	printf("\n%s", ft_strdup(str));
// }
