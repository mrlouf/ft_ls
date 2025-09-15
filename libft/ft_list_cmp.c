/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:56:16 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 10:11:11 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./libft.h"

int	ft_lst_cmp(t_list *first, t_list *second)
{
	return (strcmp((char *)first->content, (char *)second->content));
}