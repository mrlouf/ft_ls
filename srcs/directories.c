/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:29:25 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 10:00:20 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

void    ls_get_dirs(t_ls **ls)
{
/*     if ((*ls)->args == NULL)
        ls_get_current_dir(ls); */

    DIR *dir = opendir(".");
    if (!dir)
    {
        free(ls);
        exit(1);
    }

    struct dirent *entry;
    entry = readdir(dir);
    while (entry)
    {
        if (ft_strncmp(entry->d_name, ".", 1) == 0)
        {
            entry = readdir(dir);
            continue ;
        }
        t_list *new = ft_lstnew(entry->d_name);
        if (!new)
        {
            closedir(dir);
            ls_exit(*ls, 1, "Memory allocation failed");
        }
        ft_lstadd_back((void *)&(*ls)->dirs, new);

        entry = readdir(dir);
    }

    closedir(dir);

	ft_list_sort(&(*ls)->dirs, &ft_lst_cmp);

    t_list *tmp = (*ls)->dirs;
    while (tmp)
    {
        ft_printf("%s  ", (char *)tmp->content);
        tmp = tmp->next;
    }
    ft_printf("\n");
}
