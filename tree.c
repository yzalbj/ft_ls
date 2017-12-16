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

void    ft_recursivels(t_node *tree, t_opt *opt, char *path)
{
    if (tree && tree->left)
        ft_recursivels(tree->left, opt, path);
    if (tree && tree->stat->mode[0] == 'd')
        ft_ls(opt, ft_createpath(path, tree->stat->name));
    if (tree && tree->right)
        ft_recursivels(tree->right, opt, path);
}

void ft_place_node(t_node **root, struct dirent *file, const char *path)
{
    t_node  *root_tmp;
    t_node  *tmp_node;
    t_node  *node;

    root_tmp = *root;
    if (root_tmp)
    {
    node = ft_create_node(file, path);
    while (root_tmp)
    {
        tmp_node = root_tmp;
        if ((ft_strcmp(root_tmp->stat->name, node->stat->name)) > 0)
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
}

t_node  *ft_create_node(struct dirent *file, const char *path)
{
    t_node  *node;

    if (!(node = (t_node *)malloc(sizeof(t_node))))
        return (NULL);
    node->left = NULL;
    node->right = NULL;
    node->stat = ft_create_stat(file, path);
    return (node);
}
