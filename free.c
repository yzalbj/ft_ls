/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:04:29 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/21 14:04:31 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"
void ft_free_node(t_node *root, t_opt *opt)
{
	ft_putendl(root->stat->name);
	free(&root->stat->name);
	if (opt->opt_l)
	{
		free(&root->stat->time);
		free(&root->stat->user);
		free(&root->stat->group);
		if (root->stat->mode[0] == 'l')
			free(root->stat->readlink);
	}
	free(&root->stat->mode);
	free(&root->stat);
	free(&root);
}
void ft_free_tree(t_node *tree, t_opt *opt)
{
	if (tree && tree->left)
		ft_free_tree(tree->left, opt);
	// if (tree && !(tree->left) && !(tree->right))
	// 	ft_free_node(tree);
	if (tree && tree->right)
		ft_free_tree(tree->right, opt);
	if (tree && !(tree->left) && !(tree->right))
		ft_free_node(tree, opt);
}
