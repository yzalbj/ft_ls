/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:06:53 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 19:07:00 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"
//
// /*
// **  SI LE RETURN EST NEGATIF, ALORS LE MOIS DE S1 EST PLUS RECENT
// */
//
// int     ft_cmpmonth(char *s1, char *s2)
// {
//     char    **all_month;
//     int     month1;
//     int     month2;
//     int     i;
//
//     i = 0;
//     all_month = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
//                 "Oct", "Nov", "Dec"};
//     while (!(ft_strnequ(s1, all_month[i], 3))
//         i++;
//     month1 = i;
//     i = 0;
//     while (!(ft_strnequ(s2, all_month[i], 3))
//         i++;
//     month2 = i;
//     return (month1 - month2);
// }
//
// /*
// **  SI LE RETURN EST NEGATIF S1 EST PLUS RECENT
// */
//
// int     ft_cmptime(char *s1, char *s2)
// {
//         int     len1;
//         int     len2;
//         int    tmp;
//
//         len1 = ft_atoi(&s1[17]);
//         len2 = ft_atoi(&s2[17]);
//         if (len1 > len2)
//             return (-1);
//         else if (len1 < len2)
//             return (1);
//         tmp = ft_cmpmonth(s1, s2);
//         if (tmp < 0)
//             return
//
// }

void    ft_recursivels(t_node *tree, t_opt *opt, char *path)
{
    if (tree && tree->left)
        ft_recursivels(tree->left, opt, path);
    if (tree && tree->stat->mode[0] == 'd' && ft_strcmp(tree->stat->name, ".")
            && ft_strcmp(tree->stat->name, ".."))
            {
                ft_putchar('\n');
                // path = (ft_createpath(path, tree->stat->name));
                ft_putstr(ft_createpath(path, tree->stat->name));
                // ft_putstr(path);
                ft_putstr(":\n");
                ft_ls(opt, ft_createpath(path, tree->stat->name));
            }
    if (tree && tree->right)
        ft_recursivels(tree->right, opt, path);
}

void ft_place_node(t_node **root, t_node *node, t_opt *opt)
{
    t_node  *root_tmp;
    t_node  *tmp_node;

    root_tmp = *root;
    while (root_tmp)
    {
        tmp_node = root_tmp;
        if (opt->opt_t)
        {
            if (root_tmp->stat->epoch < node->stat->epoch)
            {
                root_tmp = root_tmp->left;
                if (!root_tmp)
                    tmp_node->left = node;
            }
            else
            {
                root_tmp = root_tmp->right;
                if (!root_tmp)
                    tmp_node->right = node;
                }
        }
        else if ((ft_strcmp(root_tmp->stat->name, node->stat->name)) > 0)
        {
            root_tmp = root_tmp->left;
            if (!root_tmp)
                tmp_node->left = node;
        }
        else
        {
            root_tmp = root_tmp->right;
            if (!root_tmp)
                tmp_node->right = node;
        }
    }
}

t_node  *ft_create_node(struct dirent *file, char *path, t_opt *opt)
{
    t_node  *node;

    if (!(node = (t_node *)malloc(sizeof(t_node))))
        return (NULL);
    node->left = NULL;
    node->right = NULL;
    if (!(node->stat = ft_create_stat(file, path, opt)))
        return (NULL);
    return (node);
}
