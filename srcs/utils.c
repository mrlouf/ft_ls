/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:56:36 by nponchon          #+#    #+#             */
/*   Updated: 2025/11/03 12:56:54 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

bool    contains_whitespace(const char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str == '\n')
			return (true);
		str++;
	}
	return (false);
}
