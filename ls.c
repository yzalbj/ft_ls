/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:34:21 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 17:34:23 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

char    *ft_createpath(char *path, char *to_add)
{
    path = ft_strjoin(path, to_add, 'N');
    return (path);
}

char    *ft_removeslash(char *path)
{
    char    *new;

    new = ft_strnew(ft_strlen(path) - 1);
    ft_strncpy(new, path, ft_strlen(path) - 1);
    // free(path);
    return(new);
}

void ft_issymlink(t_opt *opt, t_stat *stat)
{
    if (stat->mode[0] == 'l')
    {
        ft_display_file(opt, stat);
        exit (1);
    }
}

char *ft_lastfile(char *path)
{
	char	**tab;
	char	*last_file;
	int		i;

	tab = ft_strsplit(path, '/');
	i = 0;
	while (tab[i])
		i++;
	last_file = ft_strdup(tab[i - 1]);
	while (i < 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
	return (last_file);
}

void ft_display_ls(t_opt *opt, char *path, t_node *root, int argc)
{
	static char flag;

    if (root && root->stat->mode[0] == 'd' &&
		((flag && opt->opt_R) || argc - 1 != opt->opt_nb))
    {
        ft_putstr(ft_removeslash(path));
        ft_putendl(":");
    }
    // printf("errno = %d\n", errno);
	if (errno != 0)
		ft_error(errno, path, opt);
	else
	{
		// if (argc - 1 != opt->opt_nb)
		// {
		// 	ft_putstr(path);
		// 	ft_putendl(":");
		// }
		if (opt->opt_l)
		{
			ft_putstr("total ");
			ft_putnbr(ft_calc_blocks(0, 1));
			ft_putchar('\n');
		}
		ft_display_tree(root, opt);
		// if (opt->opt_R || (argc - 1 != opt->opt_nb))
		// 	ft_putchar('\n');
		if (opt->opt_l)
		{
			ft_spaceafteruser("", 1);
			ft_spaceaftergroup("", 1);
			ft_spacebeforenlink(0, 1);
			ft_spacebeforenbytes(0, 1);
		}
		// printf("argc == %d\nopt-_nb == %d\n", argc - 1, opt->opt_nb);
		if (opt->opt_R || argc - 1 != opt->opt_nb)
			ft_putchar('\n');
		flag = 1;
	}
}

void ft_ls(t_opt *opt, char *path, int argc)
{
    DIR             *current_dir;
    t_node          *root;
    struct dirent   *current_file;
    char            *path_tmp;

    root = NULL;
    // printf("errno = %d\n", errno);
    if ((current_dir = opendir(path)))
    {
        if (opt->opt_l)
            ft_issymlink(opt, ft_create_stat(NULL, path, opt));
        path = ft_createpath(path, "/");
        // ft_putendl("salut");
        while ((current_file = readdir(current_dir)))
        {
			if (current_file->d_name[0] == '.' && !(opt->opt_a))
               continue;
			   // skip les dossier et faire tous les fichiers puis les fichiers;
			// if (current_file->d_name[0] == 'd')
			// {
			// 	ft_ls(opt, path, argc);
			// }
               path_tmp = ft_createpath(path, current_file->d_name);
               // printf("path_tmp = %s\n", path_tmp);
               if (errno != 0)
               {
                   // printf("pour path = %s\n", path);
                   ft_error(errno, path_tmp, opt);
               }
            if (!root)
                root = ft_create_node(current_file, path_tmp, opt);
            else
                ft_place_node(&root, ft_create_node(current_file, path_tmp, opt), opt);
            ft_strdel(&path_tmp);
        }
            closedir(current_dir);
    }
    // printf("path after  = %s\n", path);
    ft_display_ls(opt, path, root, argc);
    if (opt->opt_R)
        ft_recursivels(root, opt, path, argc);
}
