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

void    ft_recursivels(t_node *tree, t_opt *opt, t_path *path)
{
	char *tmp;

    if (tree && tree->left)
        ft_recursivels(tree->left, opt, path);
    if (tree && tree->stat->mode[0] == 'd' && ft_strcmp(tree->stat->name, ".")
            && ft_strcmp(tree->stat->name, ".."))
            {
				// printf("CURRENT_PATH = %s\ntree->name = %s\n", mCURRENT_PATH, tree->stat->name);
				tmp = ft_strdup(CURRENT_PATH);
				CURRENT_PATH = ft_addpath(CURRENT_PATH, tree->stat->name);
				// printf("CURRENT_PATH = %s\n", CURRENT_PATH);
				ft_ls(opt, path);
				CURRENT_PATH = tmp;
				free(tmp);
            }
    if (tree && tree->right)
        ft_recursivels(tree->right, opt, path);
}

void ft_place_node(t_node **root, t_node *node, t_opt *opt)
{
    t_node  *root_tmp;
    t_node  *tmp_node;

    root_tmp = *root;
	if (root_tmp)
    {
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
	else
		root_tmp = node;
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
