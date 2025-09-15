/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:21:39 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 15:26:21 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incs/ft_ls.h"

void    ls_parse_options(t_ls *ls)
{
	int i = -1, j = -1;

	while (ls->args[++i]) {
		if (ls->args[i][0] != '-') {
			char *filename = ft_strdup(ls->args[i]);
			if (!filename)
				ls_exit(ls, 1, "Memory allocation failed");
			ft_lstadd_back(&ls->filenames, ft_lstnew(filename));
			cucufu();
		}
		j++;
	}
    
}
