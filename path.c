/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 11:32:37 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 19:39:32 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_fillpath(char **argv, int argc, t_path *path, int i)
{
	int		j;

	j = 0;
	if (i == argc)
	{
		path->all_path[j] = ft_strdup(".");
		path->error[j] = 0;
		j++;
	}
	while (i < argc)
	{
		path->all_path[j] = ft_strdup(argv[i]);
		path->error[j] = 0;
		i++;
		j++;
	}
	path->all_path[j] = NULL;
	path->error[j] = -1;
}

t_path	*ft_createpath(char **argv, int argc, int i)
{
	t_path	*path;
	int		size;

	size = (i == argc) ? 1 : argc - i;
	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(path->all_path = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	if (!(path->error = (int *)malloc(sizeof(int) * (size + 1))))
		return (NULL);
	path->argc = argc;
	path->index = 0;
	path->sub_index = 0;
	PATH_TMP = NULL;
	ft_fillpath(argv, argc, path, i);
	return (path);
}
