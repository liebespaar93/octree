
#include <stdlib.h>

#include "ft_queue.h"

t_queue *ft_new_queue(void *data)
{
	t_queue *new;

	new = malloc(sizeof(t_queue));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

t_queue *ft_queue_add(t_queue *q_head, t_queue *q_new)
{
	t_queue	*temp;

	if (!q_head)
		return (q_new);
	temp = q_head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = q_new;
	return (q_head);
}

void	ft_queue_free(t_queue **ptr)
{
	t_queue	*temp;

	if (ptr)
	{
		if (*ptr)
		{
			temp = *ptr;
			*ptr = (*ptr)->next;
			free(temp);
		}
	}
}

int	ft_queue_len(t_queue *q)
{
	int index;

	index = 0;
	while (q)
	{
		q = q->next;
		index++;
	}
	return (index);
}

