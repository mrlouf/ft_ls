/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:27:26 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/13 12:30:40 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

// Standard libraries
# include <dirent.h>

// Libft (including ft_printf + GNL)
# include "../libft/libft.h"

// Typedefinitions (structures)
/*        
In the glibc implementation, the dirent structure is defined as follows:
    struct dirent {
        ino_t          d_ino;       // Inode number
        off_t          d_off;       // Not an offset; see below
        unsigned short d_reclen;    // Length of this record
        unsigned char  d_type;      // Type of file; not supported by all filesystem types
        char           d_name[256]; // Null-terminated filename
    };
*/

// Linked list to store directory entries (especially useful for the -R option and sorting)
typedef struct s_elem
{
    struct dirent      *entry;
    struct s_elem      *next;
}                       t_elem;

// Function prototypes
void    ls_parse_options(int argc, char **argv);
void    ls_get_dirs(int argc, char **argv);

void    ls_print_dir(DIR *dir);

#endif