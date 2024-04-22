/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:58:05 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 18:58:05 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	else
		return (0);
}

// int main(){
// 	printf("%c", ft_isalpha('a' - 1));
// 	printf("\n%c", ft_isalpha('a'));
// 	printf("\n%c", ft_isalpha('z' + 1));
// 	printf("\n%c", ft_isalpha('A' - 1));
// 	printf("\n%c", ft_isalpha('A'));
// 	printf("\n%c", ft_isalpha('Z' + 1));
// 	printf("\n%c", ft_isalpha('Z' ));
// }