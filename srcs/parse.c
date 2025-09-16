/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:21:39 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/16 13:41:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incs/ft_ls.h"

void    get_recursive_dirs(t_ls *ls)
{
	t_list *head = ls->files;
	t_list *current = NULL;

	while (head)
	{
		DIR *dir = opendir(head->content);
		if (!dir) {
			ls_perror(ls, 1, "ft_ls: cannot open directory");
			head = head->next;
			continue ;
		}
		ft_lstadd_back(&current, ft_lstnew(ft_strdup(head->content)));
		closedir(dir);
		head = head->next;
	}
	ls->dirs = current;
	return ;
}

void    ls_parse_options(t_ls *ls)
{
	int i = 0, j = 0;

	while (ls->args[i]) {
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
			j = 0;
		}
		i++;
	}

	if (ls->flag_recursive)
	{
		get_recursive_dirs(ls);
		return ;
	}

	ls->dir_entries = malloc(sizeof(t_dir_entries) * (ls->file_size + 1));
	if (!ls->dir_entries)
		ls_exit(ls, 1, "Memory allocation failed");
	ls->dir_entries[ls->file_size].dirname = NULL; // Mark the end of the array
	ls->dir_entries[ls->file_size].entries = NULL;

	if (ls->file_size == 0) {
		char *current_dir = ft_strdup(".");
		if (!current_dir)
			ls_exit(ls, 1, "Memory allocation failed");
		ft_lstadd_back(&ls->files, ft_lstnew(current_dir));
		ls->file_size = 1;
	}

	/*     ft_printf("Flags set: a=%d, l=%d, r=%d, R=%d, t=%d\n",
		ls->flag_all, ls->flag_list, ls->flag_reverse,
		ls->flag_recursive, ls->flag_time); // DEBUG: print flags */
}
