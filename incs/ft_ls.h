/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:27:26 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/17 12:41:24 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

// Standard libraries
# include <dirent.h>
# include <stdbool.h>
# include <sys/stat.h>

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

typedef struct s_dir_entries {
    char    *dirname;
    t_list  *entries; // list of entry names (or dirent pointers)
}	t_dir_entries;

// structure to keep track of visited directories so as to avoid symlink infinite loops
typedef struct s_visited {
    dev_t				dev;
    ino_t				ino;
    struct s_visited	*next;
}	t_visited;

typedef struct s_ls
{
    char                    **args;
	struct s_list		    *files;
	int					    file_size;
    struct s_dir_entries    *dir_entries; // Array of directory entries

    // Flags
    bool	flag_all;		// -a
    bool	flag_list;		// -l
    bool	flag_reverse;	// -r
    bool	flag_recursive;	// -R
    bool	flag_time;		// -t

    struct s_list       *dirs;  // Store all directories to display
}	t_ls;



// Function prototypes
void    ls_parse_options(t_ls *ls);
void    ls_get_dirs(t_ls *ls);
void	ls_get_single(t_ls *ls);
void	ls_get_multiples(t_ls *ls);

void    ls_sort_entries(t_ls *ls);

void    ls_print_dir(DIR *dir);
void	display_help(t_ls *ls);
void    ls_print_final(t_ls *ls);

void    ls_exit(t_ls *ls, int code, char *message);
void	ls_perror(t_ls *ls, int code, char *message);

#endif
