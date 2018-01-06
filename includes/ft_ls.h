/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 12:08:28 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/06 18:44:28 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <errno.h>

# define FALSE_OPT -1
# define FILE 1
# define DIRECTORY 2
# define ERROR 0
# define CURRENT_PATH (path->all_path[path->index])
# define PATH_TMP path->path_tmp
# define CYAN "\e[0;36m"
# define BACKGROUND_CYAN "\e[46m"
# define BOLD_CYAN "\e[1;36m"
# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define BACKGROUND_RED "\e[41m"
# define MAGENTA "\e[0;35m"
# define GREEN "\e[0;32m"
# define BACKGROUND_GREEN "\e[42m"
# define YELLOW "\e[0;33m"
# define BACKGROUND_YELLOW "\e[43m"
# define BLUE "\e[0;34m"
# define RESET "\e[0m"

typedef struct		s_col
{
	int				column;
	int				elempercol;
	int				tmp_elem;
	int				tmp_col;
}					t_col;

typedef struct		s_path
{
	char			**all_path;
	char			*path_tmp;
	int				index;
	int				sub_index;
	int				argc;
	int				*error;
	char			dir_or_file;
}					t_path;

typedef	struct		s_opt
{
	char			opt_l;
	char			opt_r;
	char			opt_a;
	char			opt_upperr;
	char			opt_t;
	char			opt_uppert;
	char			opt_upperg;
	char			opt_nb;
}					t_opt;

typedef	struct		s_stat
{
	char			*mode;
	char			*time;
	char			*year;
	long			epoch_sec;
	long			epoch_nsec;
	char			*user;
	char			*group;
	int				nlink;
	int				size[2];
	char			*name;
	char			*readlink;
}					t_stat;

typedef	struct		s_node
{
	t_stat			*stat;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

void				ft_free_tree(t_node **root, t_opt *opt);
void				ft_free_node(t_node **root, t_opt *opt);
int					ft_timecmp(t_stat *root, t_stat *node);
void				ft_freetab(char ***tab);
void				ft_freepath(t_path **path);
void				ft_display_opt_uppert(t_stat *stat);
void				ft_display_time(t_opt *opt, t_stat *stat);
void				ft_display_ls(t_opt *opt, t_path *path, t_node *root);
char				*ft_findmode(mode_t st_mode);
void				ft_start_ls(t_opt *opt, t_path *path);
void				ft_sortargv(t_path *path, t_opt *opt);
void				ft_columns(t_node *tree, t_opt *opt);
int					ft_nbandsize_elem(t_node *tree, int flag);
void				ft_putcolor(t_stat *stat);
int					ft_major(dev_t _x);
int					ft_minor(dev_t _x);

/*
**	PATH.C
*/

t_path				*ft_createpath(char **argv, int argc, int i);

/*
**	ERROR.C
*/

void				ft_error(int err, t_path *path, t_opt *opt);
t_node				*ft_error2(t_path *path, t_opt *opt);

/*
**	OPTION.C
*/

t_opt				*ft_opt(int argc, char **argv, int *i);

/*
**	STAT.C
*/

t_stat				*ft_create_stat(struct dirent *file, char *path,
						t_opt *opt);

/*
**	CALC_SPACE.C
*/

void				ft_resetspaces(void);
char				ft_spacebeforenlink(int nlink, int reset);
char				ft_spacebeforenbytes(int size, int reset,
						char mode, int index);
int					ft_calc_blocks(int blocks, int reset);
int					ft_spaceafteruser(char *user, int reset);
int					ft_spaceaftergroup(char *group, int reset);

/*
**	LS.C
*/

t_node				*ft_ls(t_opt *opt, t_path *path);
void				ft_lsfile(t_opt *opt, t_path *path);
void				ft_lserror(t_opt *opt, t_path *path);
char				*ft_addpath(char *path, char *to_add, char part_free);
void				ft_printwithoutslash(char *path);
char				*ft_lastfile(char *path);
/*
**	TREE.c
*/

t_node				*ft_create_node(struct dirent *file, char *path,
						t_opt *opt);
void				ft_place_node(t_node **root, t_node *node, t_opt *opt);
void				ft_recursivels(t_node *tree, t_opt *opt, t_path *path);

/*
**	DISPLAY.c
*/

void				ft_display_tree(t_node *tree, t_opt *opt);
void				ft_display_file(t_opt *opt, t_stat *stat);
#endif
