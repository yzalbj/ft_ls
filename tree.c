/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:06:53 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 19:16:20 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_recursivels(t_node *tree, t_opt *opt, t_path *path)
{
	char	*tmp;

	path->sub_index = 1;
	if (opt->opt_r && tree && tree->right)
		ft_recursivels(tree->right, opt, path);
	else if (!opt->opt_r && tree && tree->left)
		ft_recursivels(tree->left, opt, path);
	if (tree && tree->stat->mode[0] == 'd' && ft_strcmp(tree->stat->name, ".")
		&& ft_strcmp(tree->stat->name, ".."))
	{
		tmp = ft_strdup(CURRENT_PATH);
		CURRENT_PATH = ft_addpath(CURRENT_PATH, tree->stat->name, 'L');
		ft_ls(opt, path);
		ft_strdel(&CURRENT_PATH);
		CURRENT_PATH = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	if (opt->opt_r && tree && tree->left)
		ft_recursivels(tree->left, opt, path);
	else if (!opt->opt_r && tree && tree->right)
		ft_recursivels(tree->right, opt, path);
}

int		ft_accordingtotime(t_node **root_tmp, t_node *node)
{
	t_node	*tmp_node;
	int		time_diff;

	tmp_node = *root_tmp;
	time_diff = ft_timecmp((*root_tmp)->stat, node->stat);
	if (time_diff == 1)
	{
		*root_tmp = (*root_tmp)->left;
		if (!*root_tmp)
			tmp_node->left = node;
	}
	else if (time_diff == -1)
	{
		*root_tmp = (*root_tmp)->right;
		if (!*root_tmp)
			tmp_node->right = node;
	}
	else
		return (0);
	return (1);
}

void	ft_accordingtoascii(t_node **root_tmp, t_node *node)
{
	t_node	*tmp_node;

	tmp_node = *root_tmp;
	if (ft_strcmp((*root_tmp)->stat->name, node->stat->name) > 0)
	{
		*root_tmp = (*root_tmp)->left;
		if (!*root_tmp)
			tmp_node->left = node;
	}
	else
	{
		*root_tmp = (*root_tmp)->right;
		if (!*root_tmp)
			tmp_node->right = node;
	}
}

void	ft_place_node(t_node **root, t_node *node, t_opt *opt)
{
	t_node	*root_tmp;
	int		flag_time;

	root_tmp = *root;
	if (!node)
		return ;
	ft_nbandsize_elem(node, 0, 0);
	while (root_tmp)
	{
		flag_time = 0;
		if (opt->opt_t)
			flag_time = ft_accordingtotime(&root_tmp, node);
		if (!flag_time)
			ft_accordingtoascii(&root_tmp, node);
	}
}

t_node	*ft_create_node(struct dirent *file, char *path, t_opt *opt)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	if (!(node->stat = ft_create_stat(file, path, opt)))
	{
		ft_memdel((void **)&node);
		return (NULL);
	}
	return (node);
}
