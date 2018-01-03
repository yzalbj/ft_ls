/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:01:27 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 16:33:19 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void ft_sortargvascii(int argc, char **argv, int i)
{
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			ft_swapstr(&argv[i], &argv[i + 1]);
			i = 1;
		}
		i++;
	}
}

void ft_sorterror(t_path *path)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (path->all_path[i])
	{
		if (path->error[i])
		{
			j = i;
			while (path->error[j] && path->error[j] != -1)
				j++;
			if (path->error[j] == -1)
				return ;
			ft_swapstr(&path->all_path[i], &path->all_path[i + 1]);
			path->error[i] = 0;
			path->error[i + 1] = 1;
			i = 1;
		}
		i++;
	}
}

void ft_sortargv(t_path *path, t_opt *opt)
{
	t_stat	*first;
	t_stat	*second;
	int		i;

	i = 0;
	ft_sorterror(path);
	while (!path->error[i + 1] && path->all_path[i + 1])
	{
		if (opt->opt_t)
		{
			first = ft_create_stat(NULL, path->all_path[i], opt);
			second = ft_create_stat(NULL, path->all_path[i + 1], opt);
			if (!opt->opt_r && ft_timecmp(first, second) == 1)
			{
				ft_swapstr(&path->all_path[i], &path->all_path[i + 1]);
				i = 1;
			}
			else if (opt->opt_r && ft_timecmp(first, second) == -1)
			{
				ft_swapstr(&path->all_path[i], &path->all_path[i + 1]);
				i = 1;
			}
			free(first);
			free(second);
		}
		else if (opt->opt_r && ft_strcmp(path->all_path[i], path->all_path[i + 1]) < 0)
		{
			ft_swapstr(&path->all_path[i], &path->all_path[i + 1]);
			i = 0;
		}
			i++;
	}
}

void ft_start_ls(t_opt *opt, t_path *path)
{
	path->dir_or_file = ERROR;
	while (CURRENT_PATH)
	{
		ft_lserror(opt, path);
		path->index++;
	}
	ft_sortargv(path, opt);
	path->index = 0;
	path->dir_or_file = FILE;
	ft_lsfile(opt, path);
	path->dir_or_file = DIRECTORY;
	path->index = 0;
	while (CURRENT_PATH)
	{
		ft_ls(opt, path);
		path->index++;
	}
}

int		main(int argc, char **argv)
{
		t_opt	*opt;
		t_path	*path;
		int		i;

		i = 1;
		opt = ft_opt(argc, argv, &i);
		if (opt != NULL)
		{
			ft_sortargvascii(argc, argv, i);
			path = ft_createpath(argv, argc, i);
			if (path)
			{
				if (argc == opt->opt_nb)
				{
					path->dir_or_file = DIRECTORY;
					ft_ls(opt, path);
				}
				else
					ft_start_ls(opt, path);
			}
			free(opt);
			opt = NULL;
			ft_freepath(&path);
		}
		else
			return (1);
	return (0);
}
