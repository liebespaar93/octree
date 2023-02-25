
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

#include "my_otc_tree.h"

t_otc_tree	*ft_otc_tree_head_set(t_queue *position_list, double *f(void *))
{
	t_otc_tree	*head;
	double		*position;
	int			i;

	if (!position_list)
		return (NULL);
	head = malloc(sizeof(t_otc_tree));
	if (!head)
		return (NULL);
	bzero(head, sizeof(t_otc_tree));
	while (position_list)
	{
		i = 0;
		position = f(position_list->data);
		while (i < 3)
		{
			if (head->size < fabs(position[i]))
				head->size = position[i];
		}
		position_list = position_list->next;
	}	
}

int	ft_next_otc_type(t_otc_tree *now, t_otc_tree *new, bool *allow[3])
{
	int	type;

	type = 0;
	(*allow)[0] = now->position[0] - new->position[0] > 0;
	(*allow)[1] = now->position[1] - new->position[1] > 0;
	(*allow)[2] = now->position[2] - new->position[2] > 0;
	if ((*allow)[0])
		type += 4;
	if ((*allow)[1])
		type += 2;
	if ((*allow)[2])
		type += 1;
	return (type);
}

t_otc_tree  *ft_otc_tree_child(t_otc_tree *parent, bool allow[3])
{
    t_otc_tree  *otc;

    otc = malloc(sizeof(t_otc_tree));
    if (!otc)
        return (NULL);
	bzero(otc, sizeof(t_otc_tree));
	otc->deep =  parent->deep + 1;
	otc->size = parent->size * 0.5;
	otc->position[0] = parent->position[0] + (otc->size * (-1.0 + 2.0 * allow[0]));
	otc->position[1] = parent->position[1] + (otc->size * (-1.0 + 2.0 * allow[1]));
	otc->position[2] = parent->position[2] + (otc->size * (-1.0 + 2.0 * allow[2]));
    return (0);
}

void	ft_otc_add(t_otc_tree *now, double new[3], void *data)
{
	int		deep;
	int		type;
	bool	allow[3];

	type = ft_next_otc_type(now, new, &allow);
	now->data_list = ft_queue_add(now->data_list, ft_new_queue(data));
	if (now->next[type])
		ft_otc_add(now->next[type], new, data);
	else
	{
		now->next[type] = ft_otc_tree_child(now, allow);
	}

}
