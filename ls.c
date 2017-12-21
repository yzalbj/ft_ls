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

char    *ft_addpath(char *path, char *to_add)
{
    path = ft_strjoin(path, to_add, 'N');
    return (path);
}

char    *ft_removeslash(char *path)
{
    char    *new;

    new = ft_strnew(ft_strlen(path) - 1);
    ft_strncpy(new, path, ft_strlen(path) - 1);
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
	int		len;

	len = ft_strlen(path);
	while (len >= 0)
	{
		if (path[len] == '/')
			break ;
		len--;
	}
	return (&path[len + 1]);
}

void ft_display_ls(t_opt *opt, t_path *path, t_node *root)
{
	static char flag;

printf("PATH === %s\n", CURRENT_PATH);
// 	if (root)
// 	printf("name == %s\nmode == %s\n", root->stat->name, root->stat->mode);
	// printf("flag == %d\n", flag);
	// if (path->dir_or_file == DIRECTORY && flag)
	// 	ft_putchar('\n');
	// printf("index = %d\n", path->index);
	if (CURRENT_PATH)
    {
		if (path->index > 0)
			ft_putchar('\n');
		ft_putstr(ft_removeslash(CURRENT_PATH));
	// else
	// 		ft_putstr(CURRENT_PATH);
		ft_putendl(":");
	}
    // printf("errno = %d\n", errno);
	if (errno != 0)
		ft_error(errno, path, opt);
	else
	{
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
		// printf("argc == %d\nopt-_nb == %d\n", path->argc - 1, opt->opt_nb);
		// if (opt->opt_R || path->argc - 1 != opt->opt_nb)
		// 	ft_putchar('\n');
		flag = 1;
		// ft_free_tree(root, opt);
	}
}

t_node *ft_ls(t_opt *opt, t_path *path)
{
    DIR             *current_dir;
    struct dirent   *current_file;
	t_node          *root;

    root = NULL;
	// printf("dir_or_char == %d\n", path->dir_or_file);
    if ((current_dir = opendir(CURRENT_PATH)))
    {
		if (path->dir_or_file != DIRECTORY)
		{
			path->index++;
			ft_ls(opt, path);
			closedir(current_dir);
			return (root);
		}
        if (opt->opt_l)
            ft_issymlink(opt, ft_create_stat(NULL, CURRENT_PATH, opt));
        CURRENT_PATH = ft_addpath(CURRENT_PATH, "/");
        while ((current_file = readdir(current_dir)))
        {
			if (current_file->d_name[0] == '.' && !(opt->opt_a))
               continue;
              PATH_TMP = ft_addpath(CURRENT_PATH, current_file->d_name);
               if (errno != 0)
               {
                   ft_error(errno, path, opt);
               }
            if (!root)
                root = ft_create_node(current_file, PATH_TMP, opt);
            else
                ft_place_node(&root, ft_create_node(current_file, PATH_TMP, opt), opt);
            ft_strdel(&PATH_TMP);
        }
            closedir(current_dir);
    }
	if (errno == ENOTDIR)
		return (ft_error2(path, opt));
    ft_display_ls(opt, path, root);
	// printf("path = %s\n", CURRENT_PATH);
    if (opt->opt_R)
        ft_recursivels(root, opt, path);
	return (NULL);
}

void ft_lsfile(t_opt *opt, t_path *path)
{
	t_node *root;
	t_node *node;

	root = NULL;
	while (path->index < path->argc - opt->opt_nb)
	{
		// printf("index == %d\n", path->index);
		node = ft_ls(opt, path);
		if (!root && node)
			root = node;
		else if (node)
			ft_place_node(&root, node, opt);
		path->index++;
	}
	ft_display_ls(opt, path, root);
	if (path->index == path->argc)
		ft_putchar('\n');
}
