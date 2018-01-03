
#include "./includes/ft_ls.h"
/*
** si FT_TIMECMP == 1 alors le temps de node est PLUS RECENT que celui de root
** si FT_TIMECMP == -1 alors le temps de node est PLUS VIEUX que celui de root
** si FT_TIMECMP == 0 alors le temps de node est EGAL a celui de root
*/

int	ft_timecmp(t_stat *root, t_stat *node)
{
	if (root->epoch_sec < node->epoch_sec)
		return (1);
	else if (root->epoch_sec > node->epoch_sec)
		return (-1);
	else if (root->epoch_nsec < node->epoch_nsec)
		return (1);
	else if (root->epoch_nsec > node->epoch_nsec)
		return (-1);
	else
		return (0);
}

char *ft_lastfile(char *path)
{
	int		len;

	len = ft_strlen(path);
	while (len >= 0)
	{
		if (path[len] == '/')
			break ;
		len--;
	}
	return (&path[len + 1]);
}

char    *ft_removeslash(char *path)
{
	char    *new;

	if (!path)
		return (NULL);
	if (path[ft_strlen(path) - 1] == '/')
	{
		new = ft_strnew(ft_strlen(path) - 1);
		ft_strncpy(new, path, ft_strlen(path) - 1);
		return (new);
	}
	return(path);
}

char    *ft_addpath(char *path, char *to_add, char part_free)
{
	char *new;

	new = ft_strjoin(path, to_add, part_free);
	return (new);
}

int		ft_calc_blocks(int blocks, int reset)
{
	static int	total;
	int			tmp;

	total += blocks;
	tmp = total;
	if (reset)
		total = 0;
	return (tmp);
}
