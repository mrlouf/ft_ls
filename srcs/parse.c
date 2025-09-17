/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:21:39 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/17 08:56:30 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incs/ft_ls.h"

/*
	Collect all paths to collect to later call ls_get_multiples or ls_get_single
	insteaf of collecing recursively (less complex).
 */
void collect_recursive_paths(char *path, t_list **recursive_list, t_ls *ls)
{
	DIR *dir = opendir(path);
	if (!dir)
		return;

	t_list *new_dir = ft_lstnew(ft_strdup(path));
	ft_lstadd_back(recursive_list, new_dir);

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.' && !ls->flag_all)
			continue;
		if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
			continue;
			
		if (entry->d_type == DT_DIR) {
			char full_path[PATH_MAX];
			snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
			collect_recursive_paths(full_path, recursive_list, ls);
		}
	}
	closedir(dir);
}

int		count_recursive_dirs(const char *path, t_ls *ls)
{
	DIR *dir = opendir(path);
	if (!dir) {
		perror("ft_ls: cannot open directory");
		return (0);
	}

	int count = 1;

	struct dirent *entry;
	entry = readdir(dir);
	while (entry) {
		
		if (entry->d_name[0] == '.' ) {
			entry = readdir(dir);
			continue;
		}

		if (entry->d_type == DT_DIR) {
			char full_path[PATH_MAX];	// store the entire path, not just the name
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
			count += count_recursive_dirs(full_path, ls);
		}
		
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

void	get_recursive_dirs(t_ls *ls)
{
	t_list	*head = ls->files;
	t_list	*recursive_list = NULL;
	int		total_count = 0;
	
	while (head)
	{
		DIR *dir = opendir(head->content);
		if (!dir) {
			ls_perror(ls, 1, "ft_ls: cannot open directory");
			head = head->next;
			continue;
		}
		closedir(dir);

		total_count = count_recursive_dirs(head->content, ls);
		head = head->next;
	}

	ft_printf("Total directories to process recursively: %d\n", total_count); // DEBUG

	head = ls->files;
    while (head) {
        collect_recursive_paths(head->content, &recursive_list, ls);
        head = head->next;
    }

    ft_lstclear(&ls->files, free);
    ls->files = recursive_list;
    ls->file_size = total_count;

	ls->dir_entries = malloc(sizeof(t_dir_entries) * (total_count + 1));
	if (!ls->dir_entries)
		ls_exit(ls, 1, "Memory allocation failed");

	ls->dir_entries[total_count].dirname = NULL;
	ls->dir_entries[total_count].entries = NULL;
	ls->file_size = total_count;

	return;
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
	ls->dir_entries[ls->file_size].dirname = NULL;
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
