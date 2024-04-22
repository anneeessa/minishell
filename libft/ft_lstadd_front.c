/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:58:48 by anmohamm          #+#    #+#             */
/*   Updated: 2024/02/16 18:58:48 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main()
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	lst->content = (char *)"3";
// 	lst->next = NULL;
// 	t_list *new = malloc(sizeof(t_list));
// 	new->content = (char *)"2";
// 	new->next = NULL;

//  ft_lstadd_front(&lst, new);
// 	t_list *curr;
// 	curr = lst;
// 	while (curr != NULL)
// 	{
// 		printf("%s\n", (char *)(curr->content));
// 		curr = curr->next;
// 	}
// }