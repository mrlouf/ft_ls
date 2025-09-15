/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:23:28 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/15 09:38:43 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

static void ls_init(t_ls **ls, char **av)
{
    (*ls)->args = ++av;

    // Initialize flags to 0
    (*ls)->flag_all = 0;
    (*ls)->flag_list = 0;
    (*ls)->flag_reverse = 0;
    (*ls)->flag_recursive = 0;
    (*ls)->flag_time = 0;

    (*ls)->dirs = NULL;
}

int main(int ac, char **av)
{
    (void)ac;
    print_array(av); // DEBUG: print the arguments received

    t_ls *ls = malloc(sizeof(t_ls));
    if (!ls)
        ls_exit(ls, 1, "Memory allocation failed");

    ls_init(&ls, av);
    ls_parse_options(&ls);

    ls_get_dirs(&ls);

    free(ls);

    return (0);
}
