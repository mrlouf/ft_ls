/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:29:25 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/30 18:02:10 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

void	ls_get_single(t_ls *ls)
{
	DIR *dir = opendir(ls->files->content);
	if (!dir) {
		ls_perror(ls, 1, "ft_ls: cannot open directory");
	}

	t_list *current = NULL;
	ls->dir_entries[0].dirname = ft_strdup(ls->files->content);
	if (!ls->dir_entries[0].dirname)
	{
		closedir(dir);
		ls_exit(ls, 1, "Memory allocation failed");
	}
	ls->dir_entries[0].entries = NULL;

	struct dirent *entry;
	entry = readdir(dir);

	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1) == 0 && !ls->flag_all)
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
		ft_lstadd_back((void *)&current, new);
		ls->dir_entries[0].entries = current;

		entry = readdir(dir);
	}
	closedir(dir);

	return ;
}

void	ls_get_multiples(t_ls *ls)
{
	t_list *head = ls->files;
	t_list *current = NULL;
	int		i = 0;

	while (head) {
		DIR *dir = opendir(head->content);
		if (!dir) {
			perror("Cannot open directory");
			head = head->next;
			continue;
		}

		struct dirent *entry;
		entry = readdir(dir);

		ls->dir_entries[i].dirname = ft_strdup(head->content);
		if (!ls->dir_entries[i].dirname)
		{
			closedir(dir);
			ls_exit(ls, 1, "Memory allocation failed");
		}
		ls->dir_entries[i].entries = NULL;

		while (entry)
		{
			if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0) {
				entry = readdir(dir);
				continue;
			}
			if (ft_strncmp(entry->d_name, ".", 1) == 0 && !ls->flag_all)
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
			ft_lstadd_back((void *)&current, new);

			entry = readdir(dir);
		}

		ls->dir_entries[i].entries = current;
		current = NULL;
		i++;
		closedir(dir);

		head = head->next;
	}
}

void    ls_get_dirs(t_ls *ls)
{
	if (ls->file_size == 1)
		ls_get_single(ls);
	else
		ls_get_multiples(ls);

	return ;
}
