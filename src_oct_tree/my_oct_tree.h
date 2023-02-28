#ifndef MY_OCT_TREE_H
# define MY_OCT_TREE_H

#include <stdbool.h>

#include "ft_queue.h"


typedef struct s_oct_tree   t_oct_tree;

typedef struct s_oct_tree
{
    double	position[3];
	int		deep;
	t_queue	*data_list;
    int     data_index;
    double  size;

    t_oct_tree  *next[8];

}   t_oct_tree;

t_oct_tree	*ft_oct_tree_head_set(t_queue *position_list, double *f_get_position(void *));
int	ft_next_oct_type(t_oct_tree *now, double *new, bool (*allow)[3]);
t_oct_tree  *ft_oct_tree_child(t_oct_tree *parent, bool allow[3]);
void	ft_oct_add(t_oct_tree *now, void *data, double *f_get_position(void *));



void	ft_print_oct_tree(t_oct_tree *head, double *f_get_position(void *));
#endif
