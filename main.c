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

void ft_sortargv(int argc, char **argv, int i)
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
int		main(int argc, char **argv)
{
		t_opt	*opt;
		int		i;

		i = 1;
		opt = ft_opt(argc, argv, &i);
			//	printf("opt_l = %d\nopt_r = %d\nopt_a = %d\nopt_R = %d\nopt_t = %d\n",
				//opt->opt_l, opt->opt_r, opt->opt_a, opt->opt_R, opt->opt_t);
		if (argc == 1)
					ft_ls(opt, ".");
		else
		{
			ft_sortargv(argc, argv, i);
			while (i < argc)
			{
				if (i != argc - 1)
				{
					ft_putstr(argv[i]);
					ft_putstr(":\n");
				}
				ft_ls(opt, argv[i]);
				if (i != argc - 1)
					ft_putchar('\n');
				i++;
			}
		}
		free(opt);
	return (0);
}