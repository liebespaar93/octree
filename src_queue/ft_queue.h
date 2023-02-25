#ifndef FT_QUEUE_H
# define FT_QUEUE_H

typedef	struct s_queue	t_queue;

typedef	struct s_queue
{
	void	*data;
	t_queue		*next;
}t_queue;

t_queue *ft_new_queue(void *data);
void	ft_queue_free(t_queue **ptr);
t_queue *ft_queue_add(t_queue *q_head, t_queue *q_new);
int		ft_queue_len(t_queue *q);

#endif
