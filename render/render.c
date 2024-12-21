/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:45:15 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/21 22:20:55 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>

static void	draw_nodes(t_grid_node *node) __attribute__((hot));
int			draw_loop(t_grid_node *node) __attribute__((hot));

int	key_press(int keycode)
{
	t_engine		*engine;
	static double	offset = 0.1;

	engine = engine_instance();
	if (!engine)
		return (1);
	if (keycode == 'e')
		engine->rot_x += offset;
	if (keycode == 'd')
		engine->rot_x -= offset;
	if (keycode == 'r')
		engine->rot_y += offset;
	if (keycode == 'f')
		engine->rot_y -= offset;
	if (keycode == 't')
		engine->rot_z += offset;
	if (keycode == 'g')
		engine->rot_z -= offset;
	if (keycode == 65451)
		engine->zoom += 0.5;
	if (keycode == 65453)
		engine->zoom -= 0.5;
	engine->to_update = true;
	return (0);
}

static void	draw_nodes(t_grid_node *node)
{
	int			color;

	while (node)
	{
		color = node->color > 0 ? node->color : 0xffffff;
		if (node->n_neighbors >= 1)
			gs_line(node, node->neighbors[0]);
		if (node->n_neighbors == 2)
			gs_line(node, node->neighbors[1]);
		node = node->next;
	}
}

void	clear_image(void)
{
	int			*image;
	int			i;
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return ;
	image = (int *)engine->img->addr;
	i = 0;
	while (i < (engine->img->line_length >> 2) * engine->config.height)
	{
		image[i] = 0x000000;
		i++;
	}
}

int	draw_loop(t_grid_node *node)
{
	t_engine	*engine;

	BENCHMARK_START();
	engine = engine_instance();
	if (!engine)
		return (1);
	clear_image();
	set_crosshair();
	draw_nodes(node);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->content, 0,
		0);
	// engine->rot_y += 0.05;
	// engine->rot_x += 0.02;
	// engine->rot_z -= 0.02;
	BENCHMARK_END();
	return (0);
}

int	main(int argc, char **argv)
{
	t_engine	*engine;
	t_grid_node	*head;
	t_grid_node	*current;

	if (argc != 2)
		return (1);
	engine = engine_instance();
	if (!engine)
		return (1);
	if (!engine_init())
		return (1);
	head = map_nodes(argv[1]);
	if (!head)
		return (1);
	current = head;
	while (current)
	{
		current->coords.z *= -0.1;
		current = current->next;
	}
	engine->rot_x = 45;
	engine->rot_y = 35.264;
	engine->rot_z = 28.264;
	// engine->rot_x = 68.4;
	// engine->rot_y = 43.05;
	// engine->rot_z = 14.5;
	mlx_loop_hook(engine->mlx, &draw_loop, head);
	mlx_key_hook(engine->win, &key_press, 0);
	mlx_loop(engine->mlx);
	return (0);
}
