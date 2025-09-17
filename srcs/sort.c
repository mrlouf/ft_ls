/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:23:28 by nicolas           #+#    #+#             */
/*   Updated: 2025/09/17 09:54:21 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

void	ls_sort_entries(t_ls *ls)
{
    int i = 0;

    while (i < ls->file_size)
    {
        if (ls->flag_reverse) {
            ft_list_reverse(&ls->dir_entries[i].entries, &ft_lst_cmp);
        } else { 
            ft_list_sort(&ls->dir_entries[i].entries, &ft_lst_cmp);
        }
        i++;
    }
    return ;
}
