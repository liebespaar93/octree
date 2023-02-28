# octree

cd minilibx_opengl_20191021
make 
cp libmlx.a ../
cd ..

cc main.c src_oct_tree/my_oct_tree.c src_queue/ft_queue.c src_mlx/*.c  -I ./src_queue -I ./src_oct_tree -I src_mlx -L ./ -lmlx -lm -framework OpenGL -framework AppKit

./a.out