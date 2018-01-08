/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:28:51 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 19:17:32 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_initopt(t_opt **opt, char **argv, int i, int *j)
{
	while (argv[i][*j] == 'l' || argv[i][*j] == 'r' || argv[i][*j] == 'a'
			|| argv[i][*j] == 'R' || argv[i][*j] == 't' || argv[i][*j] == 'T'
			|| argv[i][*j] == '1' || argv[i][*j] == 'G')
	{
		if (!(*opt)->opt_l && argv[i][*j] == 'l')
			(*opt)->opt_l = 1;
		else if (!(*opt)->opt_r && argv[i][*j] == 'r')
			(*opt)->opt_r = 1;
		else if (!(*opt)->opt_a && argv[i][*j] == 'a')
			(*opt)->opt_a = 1;
		else if (!(*opt)->opt_upperr && argv[i][*j] == 'R')
			(*opt)->opt_upperr = 1;
		else if (!(*opt)->opt_t && argv[i][*j] == 't')
			(*opt)->opt_t = 1;
		else if (!(*opt)->opt_uppert && argv[i][*j] == 'T')
			(*opt)->opt_uppert = 1;
		else if (!(*opt)->opt_upperg && argv[i][*j] == 'G')
			(*opt)->opt_upperg = 1;
		else if (!(*opt)->opt_1 && argv[i][*j] == '1')
			(*opt)->opt_1 = 1;
		(*j)++;
	}
}

int		ft_isvalid_opt(char **argv, int i, int j)
{
	if (argv[i][j] != 'l' && argv[i][j] != 'r' && argv[i][j] != 'a' &&
			argv[i][j] != 'R' && argv[i][j] != 't' && argv[i][j] != '\0'
			&& argv[i][j] != 'T' && argv[i][j] != '1' && argv[i][j] != 'G')
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		if (argv[i][j] != 'l' || argv[i][j] != 'r' || argv[i][j] != 'a' ||
			argv[i][j] != 'R' || argv[i][j] != 't' || argv[i][j] != 'T' ||
			argv[i][j] != '1' || argv[i][j] != 'G')
			ft_putchar_fd(argv[i][j], 2);
		else
			ft_putchar_fd(' ', 2);
		ft_putchar_fd('\n', 2);
		ft_error(FALSE_OPT, NULL, NULL);
		return (-1);
	}
	return (1);
}

t_opt	*ft_createopt(void)
{
	t_opt	*opt;

	opt = (t_opt *)malloc(sizeof(t_opt));
	opt->opt_l = 0;
	opt->opt_r = 0;
	opt->opt_a = 0;
	opt->opt_upperr = 0;
	opt->opt_t = 0;
	opt->opt_uppert = 0;
	opt->opt_upperg = 0;
	opt->opt_1 = 0;
	return (opt);
}

t_opt	*ft_opt(int argc, char **argv, int *i)
{
	int		j;
	t_opt	*opt;

	opt = NULL;
	opt = ft_createopt();
	if (argc > 1)
	{
		while (*i < argc && argv[*i][0] == '-' && argv[*i][1])
		{
			j = 1;
			if (argv[*i][1] == '-' && !argv[*i][2])
			{
				(*i)++;
				break ;
			}
			ft_initopt(&opt, argv, *i, &j);
			if (ft_isvalid_opt(argv, *i, j) == -1)
				return (NULL);
			(*i)++;
		}
	}
	opt->opt_nb = (*i > 1 ? *i - 1 : 0);
	return (opt);
}
