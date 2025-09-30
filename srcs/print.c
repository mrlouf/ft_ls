/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:02:14 by nponchon          #+#    #+#             */
/*   Updated: 2025/09/30 18:30:02 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_ls.h"

void	display_help(t_ls *ls)
{
	ft_printf("Usage: ./ft_ls [OPTION]... [FILE]...\n\
List information about the FILEs (the current directory by default).\n\
\n\
Available options:\n\
	-a		do not ignore entries starting with .\n\
	-l		use a long listing format\n\
	-r		reverse order while sorting\n\
	-R		list subdirectories recursively\n\
	-t		sort by time, newest first\n\
\n\
	--help	display this help and exit\n");
	ls_exit(ls, 0, NULL);
}

void    ls_print_dir(DIR *dir)
{
    struct dirent *entry;
    entry = readdir(dir);
    while (entry)
    {
        if (ft_strncmp(entry->d_name, ".", 1) == 0)
        {
            entry = readdir(dir);
            continue ;
        }
        ft_printf("%s  ", entry->d_name);
        entry = readdir(dir);
    }
}

static void	print_long_format(t_ls *ls)
{
	int i = 0;
	struct stat st;
	while (i < ls->file_size)
	{
		if (ls->file_size > 1)
			ft_printf("%s:\n", ls->dir_entries[i].dirname);
		t_list *tmp = ls->dir_entries[i].entries;
		while (tmp)
		{
			if (stat((char *)tmp->content, &st) == 0) {
				// File permissions
				char permissions[11];
				mode_t mode = st.st_mode;
				permissions[0] = S_ISDIR(mode) ? 'd' : '-';
				permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
				permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
				permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
				permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
				permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
				permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
				permissions[7] = (mode & S_IROTH) ? 'r' : '-';
				permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
				permissions[9] = (mode & S_IXOTH) ? 'x' : '-';
				permissions[10] = '\0';

				// Owner and group names
				struct passwd *pw = getpwuid(st.st_uid);
				struct group *gr = getgrgid(st.st_gid);

				// Last modification time
				char *mtime = ctime(&st.st_mtime);
				mtime[ft_strlen(mtime) - 1] = '\0'; // Remove the newline character

				// Print details
				ft_printf("%s %%ld %s %s %%ld %s %s\n",
					permissions,                // File permissions
					//st.st_nlink,                // Number of hard links
					pw ? pw->pw_name : "?",     // Owner name
					gr ? gr->gr_name : "?",     // Group name
					//st.st_size,                 // File size
					mtime,                      // Last modification time
					(char *)tmp->content        // File name (full path)
				);
				tmp = tmp->next;
			} else {
				perror("stat");
			}
		}
		if (ls->file_size > 1 && i < ls->file_size - 1)
			ft_printf("\n");
		i++;
	}
	return ;
}

void    ls_print_final(t_ls *ls)
{
	if (ls->flag_list) {
		print_long_format(ls);
		return ;
	}

    int i = 0;
    while (i < ls->file_size)
    {
        if (ls->file_size > 1)
            ft_printf("%s:\n", ls->dir_entries[i].dirname);
        t_list *tmp = ls->dir_entries[i].entries;
        while (tmp)
        {
            ft_printf("%s  ", (char *)tmp->content);
            tmp = tmp->next;
        }
        if (ls->file_size > 1 && i < ls->file_size - 1)
            ft_printf("\n\n");
        i++;
    }
    ft_printf("\n");
    return ;
}
