#include "ft_queue.h"
#include "my_oct_tree.h"

#include <math.h>
#include <stdlib.h>
#include "mlx.h"

#include "ft_param.h"

double	*ft_get_data_position(void	*data)
{
	double	*org_data;

	org_data = (double *)data;
	return (org_data);
}

t_oct_tree *ft_my_oct_tree()
{
	t_oct_tree	*oct_head;
	t_queue		*a;
	double		**b;
	int			size;
	
    a = NULL;
	b = malloc(sizeof(double [3]) * (size * 2 + 1));
	for (int i = 0; i < 100; i++)
	{
		b[i + size] = malloc(sizeof(double [3]));
		b[i + size][0] = ((float)rand() / RAND_MAX) * 10.0;
		b[i + size][1] = ((float)rand() / RAND_MAX) * 10.0;
		b[i + size][2] = ((float)rand() / RAND_MAX) * 10.0;
        a = ft_queue_add(a, ft_new_queue(b[i + size]));
	}
	oct_head = ft_oct_tree_head_set(a, ft_get_data_position);
    while (a)
    {
	    ft_oct_add(oct_head, a->data, ft_get_data_position);
        a = a->next;
    }
    ft_print_oct_tree(oct_head, ft_get_data_position);
	return (oct_head);
}


void	ft_put_line_oct(t_param *param, t_oct_tree *temp)
{
	double	point[8][3];

	for (int i = 0; i < 8; i++)
	{
		point[i][0] = temp->position[0] + temp->size * (1.0 - 2.0 * (!(i & 1))) + (WIN_WIDTH * 0.5); // 임시 중앙정렬
		point[i][1] = temp->position[1] + temp->size * (1.0 - 2.0 * (!(i & 2))) + (WIN_HEIGHT * 0.5);
		point[i][2] = temp->position[2] + temp->size * (1.0 - 2.0 * (!(i & 4))) + (WIN_WIDTH * 0.5);
	}
	ft_scanline(ft_vector_2(point[0][0], point[0][1]),
		ft_vector_2(point[1][0], point[1][1]),
		param, 0x00ff00ff);
	ft_scanline(ft_vector_2(point[0][0], point[0][1]),
		ft_vector_2(point[2][0], point[2][1]),
		param, 0x000000ff);
	ft_scanline(ft_vector_2(point[1][0], point[1][1]),
		ft_vector_2(point[3][0], point[3][1]),
		param, 0x0000ffff);
	ft_scanline(ft_vector_2(point[2][0], point[2][1]),
		ft_vector_2(point[3][0], point[3][1]),
		param, 0x0000ff00);
	// for (int k = 0; k < 2; k++)
	// {
	// 	ft_scanline(ft_vector_2(point[k][0], point[k][1]),
	// 		ft_vector_2(point[k + 1][0], point[k + 1][1]),
	// 		param, 0x00ffffff);
	// 	ft_scanline(ft_vector_2(point[k][0], point[k][1]),
	// 		ft_vector_2(point[k + 2][0], point[k + 2][1]),
	// 		param, 0x00ffffff);
	// 	// ft_scanline(ft_vector_2(point[k][0], point[k][1]),
	// 	// 	ft_vector_2(point[k + 4][0], point[k + 4][1]),
	// 	// 	param, 0x00ffffff);
	// }

}

void	ft_put_point(t_param *param, double *position)
{
    int x, y;
    int color;

    x = y = -2;
	while (x < 2)
	{
		y = -2;
		while (y < 2)
		{
			ft_backbuffer_put_pixel(position[0] + x + (WIN_WIDTH * 0.5), position[1] + y + (WIN_HEIGHT * 0.5), 0x00ff3333, param); 
			// ft_backbuffer_put_pixel(position[0] + x, position[1] + y, 0x00ff3333, param); 
			y++;
		}
		x++;
	}
}

void	ft_draw_ply(t_param *param)
{
	t_oct_tree	*temp;
	t_queue		*queue;
	double		*position;
	
	temp = param->data;
	queue = ft_new_queue(temp);
	while (queue)
	{
		temp = queue->data;
		ft_put_line_oct(param, temp);
		for (int index = 0; index < 8; index++)
		{
			if (temp->next[index])
				queue = ft_queue_add(queue, ft_new_queue(((t_oct_tree *)queue->data)->next[index]));
		}
		if (temp->data_index == 1)
		{
			position = temp->data_list->data;
			ft_put_point(param, position);
		}
		ft_queue_free(&queue);
	}
}
#include <string.h>

int    ft_loop(t_param *param)
{
	//memset(param->buffer, 0, param->size_line * CANVAS_HEIGHT);
	// ft_draw_ply(param);
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, CANVAS_X, CANVAS_Y);
	return (0);
}

int main(int argc, char const *argv[])
{
///////////
	t_oct_tree	*oct_head;
	t_queue		*a;
	double		**b;
	
    a = NULL;
	int size;
	size = 50;
	b = malloc(sizeof(double [3]) * (size * 2 + 1));
	if (!b)
		return (0);
	for (int i = -size; i < size; i++)
	{
		b[i + size] = malloc(sizeof(double [3]));
		// b[i + size][0] = i * 10.0 + 100.0;
		// b[i + size][1] = i * 10.0 + 100.0;
		// b[i + size][2] = i * 10.0 + 100.0;
		b[i + size][0] = ((float)rand() / RAND_MAX) * 400.0 - 200.0;
		b[i + size][1] = ((float)rand() / RAND_MAX) * 400.0 - 200.0;
		b[i + size][2] = ((float)rand() / RAND_MAX) * 400.0 - 200.0;
        a = ft_queue_add(a, ft_new_queue(b[i + size]));
	}
	oct_head = ft_oct_tree_head_set(a, ft_get_data_position);
    while (a)
    {
	    ft_oct_add(oct_head, a->data, ft_get_data_position);
        a = a->next;
    }
    ft_print_oct_tree(oct_head, ft_get_data_position);
/////////////////

	t_param param;

    param.mlx_ptr = mlx_init();
    param.win_ptr = mlx_new_window(param.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "test");
    param.img_ptr = mlx_new_image(param.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    param.buffer = mlx_get_data_addr(param.img_ptr, &param.bits_per_pixel, &param.size_line, &param.endian);

	param.data = oct_head;
	ft_draw_ply(&param);
    mlx_put_image_to_window(param.mlx_ptr, param.win_ptr, param.img_ptr, CANVAS_X, CANVAS_Y);
	mlx_loop_hook(param.mlx_ptr, ft_loop, &param);
    mlx_loop(param.mlx_ptr);

	return 0;
}
