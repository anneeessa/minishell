/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:59:37 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 18:59:37 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// int main()
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	char *s = "3";
// 	lst->content = s;
// 	lst->next = malloc(sizeof(t_list));
// 	lst->next->content = s;
// 	lst->next->next = NULL;
// 	printf("%d", ft_lstsize(lst));
// }