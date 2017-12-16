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

void ft_ls(t_opt *opt, char *path)
{
    DIR             *current_dir;
    t_node          *root;
    struct dirent   *current_file;
    char            *path_tmp;

    root = NULL;
    //ft_putstr(path);
    //ft_putstr(":\n");
    path = ft_createpath(path, "/");
    if ((current_dir = opendir(path)))
    {
        while ((current_file = readdir(current_dir)))
        {
           if (current_file->d_name[0] == '.' && !(opt->opt_a))
               continue;
            path_tmp = ft_createpath(path, current_file->d_name);
            if (!root)
                root = ft_create_node(current_file, path_tmp);
            else
                ft_place_node(&root, current_file, path_tmp);
            ft_strdel(&path_tmp);
        }
        if (opt->opt_l)
            ft_putendl("total afaire");
        ft_display_tree(root, opt);
        //print2D(root);
    }
    else if (errno == EACCES)
    {
        ft_putstr("ft_ls: ");
        ft_putstr(path);
        ft_putendl(": Permission denied");
    }
    else if (errno == ENOTDIR)
        ft_putendl(path);
    if (opt->opt_R)
        ft_recursivels(root, opt, path);
}
