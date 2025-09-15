/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:29:25 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 18:21:14 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

static void	ls_sort_directories(t_ls *ls)
{
	if (ls->flag_reverse)
		ft_list_reverse(&ls->dirs, &ft_lst_cmp);
	else
		ft_list_sort(&ls->dirs, &ft_lst_cmp);

	return ;
}

void	ls_get_single(t_ls *ls)
{
	char *path = ".";
	if (ls->file_size == 1)
		path = ls->files->content;
	ft_printf("%s\n", path);

	DIR *dir = opendir(path);
	if (!dir)
		ls_exit(ls, 1, "Cannot open directory");

	struct dirent *entry;
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1) == 0)
		{
			entry = readdir(dir);
			continue ;
		}
		t_list *new = ft_lstnew(ft_strdup(entry->d_name));
		if (!new)
		{
			closedir(dir);
			ls_exit(ls, 1, "Memory allocation failed");
		}
		ft_lstadd_back((void *)&ls->dirs, new);

		entry = readdir(dir);
	}

	closedir(dir);
	return ;
}

void	ls_get_multiples(t_ls *ls)
{
	t_list *head = ls->files;
	while (head) {

		DIR *dir = opendir(ls->files->content);
		if (!dir)
			ls_exit(ls, 1, "Cannot open directory");

		struct dirent *entry;
		entry = readdir(dir);
		while (entry)
		{
			if (ft_strncmp(entry->d_name, ".", 1) == 0)
			{
				entry = readdir(dir);
				continue ;
			}
			t_list *new = ft_lstnew(ft_strdup(entry->d_name));
			if (!new)
			{
				closedir(dir);
				ls_exit(ls, 1, "Memory allocation failed");
			}
			ft_lstadd_back((void *)&ls->dirs, new);

			entry = readdir(dir);
		}

		closedir(dir);
		head = head->next;
	}
}

void    ls_get_dirs(t_ls *ls)
{
	if (ls->file_size > 1)
		ls_get_multiples(ls);
	else
		ls_get_single(ls);

	ls_sort_directories(ls);
}
