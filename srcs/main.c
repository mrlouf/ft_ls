/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:23:28 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/17 08:39:03 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

static void ls_init(t_ls *ls, char **av)
{
    // if no arguments, default to current directory
    ls->files = (t_list *)malloc(sizeof(t_list));
    if (!ls->files) {
        ls_exit(ls, 1, "Memory allocation failed");
    }
    ls->files->next = NULL;
    ls->files->content = ft_strdup(".");
    if (!ls->files->content) {
        free(ls->files);
        ls_exit(ls, 1, "Memory allocation failed");
    }

    ls->args = av + 1;
    
	ls->file_size = 0;
    ls->dir_entries = NULL;

    // initialise flags to 0
    ls->flag_all = 0;
    ls->flag_list = 0;
    ls->flag_reverse = 0;
    ls->flag_recursive = 0;
    ls->flag_time = 0;

    ls->dirs = NULL;
}

int main(int ac, char **av)
{
   (void)ac;

   t_ls *ls = malloc(sizeof(t_ls));
   if (!ls)
      ls_exit(ls, 1, "Memory allocation failed");

   ls_init(ls, av);
	if (ls->args != NULL) // parse if arguments provided
	    ls_parse_options(ls);

   ls_get_dirs(ls);
	ls_sort_entries(ls);
   ls_print_final(ls);

	ls_exit(ls, 0, NULL);
}
