/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:02:14 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/30 12:45:02 by nponchon         ###   ########.fr       */
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

static void	print_long_format(t_ls *ls)
{
	int i = 0;
	while (i < ls->file_size)
	{
		if (ls->file_size > 1)
			ft_printf("%s:\n", ls->dir_entries[i].dirname);
		t_list *tmp = ls->dir_entries[i].entries;
		while (tmp)
		{
			// Here you would typically gather and print detailed info
			// For simplicity, we just print the filename
			ft_printf("%s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		if (ls->file_size > 1 && i < ls->file_size - 1)
			ft_printf("\n");
		i++;
	}
	return ;
}

void    ls_print_final(t_ls *ls)
{
	if (ls->flag_list) {
		print_long_format(ls);
		return ;
	}

    int i = 0;
    while (i < ls->file_size)
    {
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
