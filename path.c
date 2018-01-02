/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 11:32:37 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/21 11:32:39 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

t_path	*ft_createpath(char **argv, int argc, int i)
{
	t_path	*path;
	int		j;
	int		size;

	j = 0;
	size = (i == argc) ? 1 : argc - i;
	// printf("size == %d\ni == %d\nargc == %d\n", size, i, argc);
	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(path->all_path = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	path->argc = argc;
	path->index = 0;
	path->sub_index = 0;
	if (i == argc)
	{
		path->all_path[j] = ft_strdup(".");
		j++;
	}
	while (i < argc)
	{
		path->all_path[j] = ft_strdup(argv[i]);
		i++;
		j++;
	}
	path->all_path[j] = NULL;
	PATH_TMP = NULL;
	// j = 0;
	// while(path->all_path[j])
	// 	ft_putendl(path->all_path[j++]);
	return (path);
}
