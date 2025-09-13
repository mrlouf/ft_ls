/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:02:14 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/13 12:20:37 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

void    ls_print_dir(DIR *dir)
{
    struct dirent *entry;
    entry = readdir(dir);
    while (entry)
    {
        ft_printf("%s\n", entry->d_name);
        entry = readdir(dir);
    }
}