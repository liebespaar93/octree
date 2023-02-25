#ifndef MY_OTC_TREE_H
# define MY_OTC_TREE_H

#include "src_queue/ft_queue.h"


typedef struct s_otc_tree   t_otc_tree;

typedef struct s_otc_tree
{
    double	position[3];
	int		deep;
	t_queue	*data_list;
    int     data_index;
    double  size;

    t_otc_tree  *next[8];

}   t_otc_tree;

#endif
