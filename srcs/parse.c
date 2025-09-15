/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:21:39 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 18:12:00 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incs/ft_ls.h"

static void	display_help(t_ls *ls)
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

void    ls_parse_options(t_ls *ls)
{
	int i = -1, j = 0;

	while (ls->args[++i]) {
		if (ft_strcmp(ls->args[i], "--help") == 0) {
			display_help(ls);
		} else if (ls->args[i][0] != '-') {
			char *filename = ft_strdup(ls->args[i]);
			if (!filename)
				ls_exit(ls, 1, "Memory allocation failed");
			ft_lstadd_back(&ls->files, ft_lstnew(filename));
			ls->file_size++;
		} else {
			while (ls->args[i][++j]) {
				if (ls->args[i][j] == 'a')
					ls->flag_all = 1;
				else if (ls->args[i][j] == 'l')
					ls->flag_list = 1;
				else if (ls->args[i][j] == 'r')
					ls->flag_reverse = 1;
				else if (ls->args[i][j] == 'R')
					ls->flag_recursive = 1;
				else if (ls->args[i][j] == 't')
					ls->flag_time = 1;
			}
		}
	}
    
}
