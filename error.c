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

// void ft_tree_single_file(char *path, t_opt *opt, int flag)
// {
// 	if (flag == 0)
// }
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
        ft_putstr("ft_ls: ");
        ft_putstr(CURRENT_PATH);
       ft_putendl(": No such file or directory");
    }
	return (NULL);
}

void	ft_error(int err, t_path *path, t_opt *opt)
{
	if (err == FALSE_OPT)
		ft_putendl_fd("usage: ft_ls [-RTalrt] [file ...]", 2);
	if (errno == EACCES)
    {
        ft_putstr("ft_ls: ");
		if (PATH_TMP)
			ft_putstr(ft_lastfile(PATH_TMP));
		else
        	ft_putstr(ft_lastfile(CURRENT_PATH));
        ft_putendl(": Permission denied");
    }
    ft_error2(path, opt);
	errno = 0;
}
