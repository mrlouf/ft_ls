/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:22:22 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/26 13:00:31 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

static void	free_all(t_ls *ls)
{
	if (ls->files)
		ft_lstclear(&ls->files, &free);
	if (ls->dirs)
		ft_lstclear(&ls->dirs, &free);
	if (ls->dir_entries) {
		for (int i = 0; i < ls->file_size; i++)
		{
			if (ls->dir_entries[i].dirname)
				free(ls->dir_entries[i].dirname);
			if (ls->dir_entries[i].entries)
				ft_lstclear(&ls->dir_entries[i].entries, &free);
		}
		free(ls->dir_entries);
	}
	if (ls)
		free(ls);
	return ;
}

void    ls_exit(t_ls *ls, int code, char *message)
{
	free_all(ls);
	if (message)
		ft_printf("Error: %s\n", message);
    exit(code);
}

void	ls_perror(t_ls *ls, int code, char *message)
{
	if (message)
		perror(message);
	free_all(ls);
	exit(code);
}
