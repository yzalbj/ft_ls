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
	while (i < argc - 1)
	{
		if (opt->opt_r && ft_strcmp(argv[i], argv[i + 1]) < 0)
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

void ft_start_ls(t_opt *opt, t_path *path, int argc)
{
	if (argc == opt->opt_nb)
	{
		path->dir_or_file = DIRECTORY;
		ft_ls(opt, path);
	}
	else
	{
		path->dir_or_file = ERROR;
		while (path->index < argc - opt->opt_nb)
		{
			ft_ls(opt, path);
			path->index++;
		}
		path->index = 0;
		path->dir_or_file = FILE;
		ft_lsfile(opt, path);
		path->dir_or_file = DIRECTORY;
		path->index = 0;
		while (path->index < argc - opt->opt_nb)
		{
			ft_ls(opt, path);
			path->index++;
		}
	}
}

int		main(int argc, char **argv)
{
		t_opt	*opt;
		t_path	*path;
		// t_node	*root;
		int		i;

		i = 1;
		opt = ft_opt(argc, argv, &i);
				// printf("opt_l = %d\nopt_r = %d\nopt_a = %d\nopt_R = %d\nopt_t = %d\n",
				// opt->opt_l, opt->opt_r, opt->opt_a, opt->opt_R, opt->opt_t);
				// printf("i == %d\nargc == %d\n",i, argc );
		if (opt)
		{
			ft_sortargv(argc, argv, i, opt);
			path = ft_createpath(argv, argc, i);
	 		if (path)
			{
				ft_start_ls(opt, path, argc);
				free(opt);
			}
		}
	exit(0);
	return (0);
}
