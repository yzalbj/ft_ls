
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
