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

void ft_sortargv(int argc, char **argv, int i, t_opt *opt)
{
	t_stat	*first;
	t_stat	*second;
	while (i < argc - 1)
	{
		if (opt->opt_t)
		{
			first = ft_create_stat(NULL, argv[i], opt);
			second = ft_create_stat(NULL, argv[i + 1], opt);
			if (!opt->opt_r && ft_timecmp(first, second) == 1)
			{
				ft_swapstr(&argv[i], &argv[i + 1]);
				i = 1;
			}
			else if (opt->opt_r && ft_timecmp(first, second) == -1)
			{
				ft_swapstr(&argv[i], &argv[i + 1]);
				i = 1;
			}
			free(first);
			free(second);
		}
		else if (opt->opt_r && ft_strcmp(argv[i], argv[i + 1]) < 0)
		{
			ft_swapstr(&argv[i], &argv[i + 1]);
			i = 1;
		}
		else if (!opt->opt_r && ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			ft_swapstr(&argv[i], &argv[i + 1]);
			i = 1;
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
		if (opt)
		{
			ft_sortargv(argc, argv, i, opt);
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
		}
		// while(1);
	// exit(0);
	return (0);
}
