
#include <math.h>
#include <stdlib.h>

#include <string.h>

#include "my_oct_tree.h"

t_oct_tree	*ft_oct_tree_head_set(t_queue *position_list, double *f_get_position(void *))
{
	t_oct_tree	*head;
	double		*position;
	int			i;

	if (!position_list)
		return (NULL);
	head = malloc(sizeof(t_oct_tree));
	if (!head)
		return (NULL);
	bzero(head, sizeof(t_oct_tree));
	while (position_list)
	{
		i = 0;
		position = f_get_position(position_list->data);
		while (i < 3)
		{
			if (head->size < fabs(position[i]))
				head->size = fabs(position[i]);
			i++;
		}
		position_list = position_list->next;
	}
	return (head);
}

int	ft_next_oct_type(t_oct_tree *now, double *new, bool (*allow)[3])
{
	int	type;

	type = 0;
	(*allow)[0] = (new[0] - now->position[0]) > 0;
	(*allow)[1] = (new[1] - now->position[1]) > 0;
	(*allow)[2] = (new[2] - now->position[2]) > 0;
	if ((*allow)[0])
		type += 1;
	if ((*allow)[1])
		type += 2;
	if ((*allow)[2])
		type += 4;
	return (type);
}

t_oct_tree  *ft_oct_tree_child(t_oct_tree *parent, bool allow[3])
{
    t_oct_tree  *oct;

    oct = malloc(sizeof(t_oct_tree));
    if (!oct)
        return (NULL);
	bzero(oct, sizeof(t_oct_tree));
	oct->deep =  parent->deep + 1;
	oct->size = parent->size * 0.5;
	oct->position[0] = parent->position[0] + (oct->size * (-1.0 + 2.0 * allow[0]));
	oct->position[1] = parent->position[1] + (oct->size * (-1.0 + 2.0 * allow[1]));
	oct->position[2] = parent->position[2] + (oct->size * (-1.0 + 2.0 * allow[2]));
    return (oct);
}

void	ft_oct_add(t_oct_tree *now, void *data, double *f_get_position(void *))
{
	int		deep;
	int		type;
	bool	allow[3];


	now->data_index++;
	now->data_list = ft_queue_add(now->data_list, ft_new_queue(data));
	if (!now->data_list)
		return ;
	if (now->deep == 5)
		type = 3;
	if (now->data_index == 1)
		return ;
	if (now->data_index == 2)
	{
		type = ft_next_oct_type(now, f_get_position(now->data_list->data), &allow);
		if (!now->next[type])
			now->next[type] = ft_oct_tree_child(now, allow);
		ft_oct_add(now->next[type], now->data_list->data, f_get_position);
	}
	type = ft_next_oct_type(now, f_get_position(data), &allow);
	if (!now->next[type])
		now->next[type] = ft_oct_tree_child(now, allow);
	ft_oct_add(now->next[type], data, f_get_position);
}

#include <stdio.h>

void	ft_print_oct_tree(t_oct_tree *head, double *f_get_position(void *))
{
	t_queue *queue;
	int			i;
	int			deep;
	t_queue		*data_list;
	queue = ft_new_queue(head);
	deep = -1;
	double *position;

	printf("\n\nprint all \n");
	while (queue)
	{
		if (deep != ((t_oct_tree *)queue->data)->deep)
		{
			deep++;
			printf("\n\ndeep[%d] \n", deep);
		}
		for (int index = 0; index < 8; index++)
		{
			if (((t_oct_tree *)queue->data)->next[index])
				queue = ft_queue_add(queue, ft_new_queue(((t_oct_tree *)queue->data)->next[index]));
		}
		data_list = ((t_oct_tree *)queue->data)->data_list;
		while (data_list)
		{
			position = f_get_position(data_list->data);
			printf("(%.2f %.2f %.2f) \t", position[0], position[1], position[2]);
			data_list = data_list->next;
		}
		fflush(stdout);
		ft_queue_free(&queue);
	}
}
