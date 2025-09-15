/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:02:14 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 10:21:44 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

void    ls_print_dir(DIR *dir)
{
    struct dirent *entry;
    entry = readdir(dir);
    while (entry)
    {
        if (ft_strncmp(entry->d_name, ".", 1) == 0)
        {
            entry = readdir(dir);
            continue ;
        }
        ft_printf("%s  ", entry->d_name);
        entry = readdir(dir);
    }
}
