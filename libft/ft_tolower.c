/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:02:32 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 19:02:32 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_tolower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = (str[i] + 32);
	}
	return (str);
}

// int main()
// {
// 	char c = 'Z';
// 	printf("%c", tolower(c));
// 	printf("\n%c", ft_tolower(c));
// }