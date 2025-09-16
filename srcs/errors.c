/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:22:22 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 16:18:41 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

static void	free_all(t_ls *ls)
{
	if (ls->files)
		ft_lstclear(&ls->files, &free);
	if (ls->dirs)
		ft_lstclear(&ls->dirs, &free);
/* 	if (ls->dir_entries)
		free_array((void **)ls->dir_entries); */
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