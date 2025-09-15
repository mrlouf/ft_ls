/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:22:22 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 09:38:59 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

void    ls_exit(t_ls *ls, int code, char *message)
{
    if (message)
        ft_printf("Error: %s\n", message);
    if (ls)
        free(ls);
    exit(code);
}
