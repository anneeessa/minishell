/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:59:18 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 18:59:18 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

// int main()
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	char *s = "3";
// 	char *s2 = "4";
// 	char *s3 = "5";

// 	lst->content = s;
// 	lst->next = malloc(sizeof(t_list));
// 	lst->next->content = s2;
// 	lst->next->next = malloc(sizeof(t_list));
// 	lst->next->next->content = s3;
// 	lst->next->next->next = NULL;
// 	printf("%s", (char *)ft_lstlast(lst)->content);
// }