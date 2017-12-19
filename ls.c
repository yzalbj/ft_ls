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
    free(path);
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
void ft_ls(t_opt *opt, char *path)
{
    DIR             *current_dir;
    t_node          *root;
    struct dirent   *current_file;
    char            *path_tmp;

    root = NULL;

     printf("path = %s\n", path);
    if ((current_dir = opendir(path)))
    {
        if (opt->opt_l)
            ft_issymlink(opt, ft_create_stat(NULL, path, opt));
        path = ft_createpath(path, "/");
        ft_putendl("salut");
        while ((current_file = readdir(current_dir)))
        {
            ft_error(errno, path, opt);
           if (current_file->d_name[0] == '.' && !(opt->opt_a))
               continue;
               path_tmp = ft_createpath(path, current_file->d_name);
            if (!root)
                root = ft_create_node(current_file, path_tmp, opt);
            else
                ft_place_node(&root, ft_create_node(current_file, path_tmp, opt), opt);
            ft_strdel(&path_tmp);
        }
        if (opt->opt_l)
        {
            //ft_issymlink(opt, ft_create_stat(NULL, ft_removeslash(path), opt));
            ft_putstr("total ");
            ft_putnbr(ft_calc_blocks(0, 1));
            ft_putchar('\n');
        }
        ft_display_tree(root, opt);
        closedir(current_dir);
        if (opt->opt_l)
        {
            ft_spaceafteruser("", 1);
           ft_spaceaftergroup("", 1);
            ft_spacebeforenlink(0, 1);
            ft_spacebeforenbytes(0, 1);
        }
    }
    ft_error(errno, path, opt);
    // if (errno == EACCES)
    // {
    //     ft_putstr("ft_ls: ");
    //     ft_putstr(path);
    //     ft_putendl(": Permission denied");
    // }
    // else if (errno == ENOTDIR)
    //     ft_display_file(opt, ft_create_stat(NULL, ft_removeslash(path), opt));
    // else if (errno == ENOENT)
    // {
    //     ft_putstr("ls: ");
    //     ft_putstr(path);
    //     ft_putendl(": No such file or directory");
    // }
        printf("path after  = %s\n", path);
    if (opt->opt_R)
        ft_recursivels(root, opt, path);
}
