/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:29:27 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 15:57:04 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

t_node *ft_error2(t_path *path, t_opt *opt)
{
	t_node	*node_file;

	if (errno == ENOTDIR && path->dir_or_file == FILE)
	{
		node_file = ft_create_node(NULL, CURRENT_PATH, opt);
		return (node_file);
	}
	else if (errno == ENOENT && path->dir_or_file == ERROR)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(CURRENT_PATH, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	return (NULL);
}

void	ft_error(int err, t_path *path, t_opt *opt)
{
	if (err == FALSE_OPT)
		ft_putendl_fd("usage: ft_ls [-RTalrt] [file ...]", 2);
	if (errno == EACCES && path->dir_or_file == DIRECTORY)
	{
		ft_putstr_fd("ft_ls: ", 2);
		if (PATH_TMP)
			ft_putstr_fd(ft_lastfile(PATH_TMP), 2);
		else
			ft_putstr_fd(ft_lastfile(CURRENT_PATH), 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	ft_error2(path, opt);
}
