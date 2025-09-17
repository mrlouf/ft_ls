/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:02:14 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/17 14:48:34 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

void	display_help(t_ls *ls)
{
	ft_printf("Usage: ./ft_ls [OPTION]... [FILE]...\n\
List information about the FILEs (the current directory by default).\n\
\n\
Available options:\n\
	-a		do not ignore entries starting with .\n\
	-l		use a long listing format\n\
	-r		reverse order while sorting\n\
	-R		list subdirectories recursively\n\
	-t		sort by time, newest first\n\
\n\
	--help	display this help and exit\n");
	ls_exit(ls, 0, NULL);
}

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

void	ls_print_single(t_ls *ls)
{
	t_list *tmp = ls->dir_entries[0].entries;

    while (tmp)
    {
        ft_printf("%s", (char *)tmp->content);
        tmp = tmp->next;
		if (tmp)
			ft_printf("  ");
	}
	ft_printf("\n");

	return ;
}

void	ls_print_multiples(t_ls *ls)
{
    int i = 0;
    while (i < ls->file_size)
    {
		if (ls->dir_entries[i].dirname == NULL) {
			i++;
			continue ;
		}
        if (ls->file_size > 1)
            ft_printf("%s:\n", ls->dir_entries[i].dirname);
        t_list *tmp = ls->dir_entries[i].entries;

        while (tmp)
        {
            ft_printf("%s  ", (char *)tmp->content);
            tmp = tmp->next;
        }
        if (ls->file_size > 1 && i < ls->file_size - 1)
            ft_printf("\n\n");
        i++;
    }
    ft_printf("\n");
	return ;
}

void    ls_print_final(t_ls *ls)
{
    if (ls->file_size == 1)
		ls_print_single(ls);
	else
		ls_print_multiples(ls);

    return ;
}
