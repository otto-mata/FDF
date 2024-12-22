/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:45:15 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/22 05:46:18 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>

static void	draw_nodes(t_grid_node *node) __attribute__((hot));
int			draw_loop(t_grid_node *node) __attribute__((hot));

int	key_press(int keycode, t_engine *engine)
{
	static int	proj = 1;

	if (keycode == XK_Escape || keycode == 'q')
		engine_exit();
	else if (keycode == 'p')
		proj ^= 1;
	if (proj)
	{
		engine->rot_x = 45;
		engine->rot_y = 35.264;
		engine->rot_z = 28.264;
	}
	else
	{
		engine->rot_x = 68.4;
		engine->rot_y = 43.05;
		engine->rot_z = 14.5;
	}
	return (0);
}

static void	draw_nodes(t_grid_node *node)
{
	int	color;

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
	long		*image;
	int			i;
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return ;
	image = (long *)engine->img->data;
	i = 0;
	while (i < (engine->img->line_length >> 3) * engine->config.height)
	{
		image[i] = 0x000000;
		i++;
	}
}

int	draw_loop(t_grid_node *node)
{
	t_engine	*engine;
	clock_t		start_time;

	start_time = clock();
	engine = engine_instance();
	if (!engine)
		return (1);
	clear_image();
	set_crosshair();
	draw_nodes(node);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->image, 0, 0);
	engine->frametime = (double)(clock() - start_time) / ((__clock_t)1000000);
	return (0);
}

int	mouse_pressed(int button, int x, int y, t_engine *engine)
{
	if (button == Button3 || button == Button1)
	{
		engine->mouse_x = x;
		engine->mouse_y = y;
		engine->set_by = button;
	}
	else if (button == Button4)
		engine->zoom += 0.1;
	else if (button == Button5)
		engine->zoom -= 0.1;
	return (0);
}

t_vec3	vec3_from_points(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = (double)(b.x - a.x) / (double)b.x;
	v.y = (double)(b.y - a.y) / (double)b.y;
	if (v.x > 1)
		v.x = 1;
	if (v.x < -1)
		v.x = -1;
	if (v.y > 1)
		v.y = 1;
	if (v.y < -1)
		v.y = -1;
	return (v);
}

int	transform_view(int x, int y, t_engine *engine)
{
	t_vec3	mouse_vec;

	if (engine->set_by == Button3)
	{
		engine->rot_x += (double)(engine->mouse_y - y) / 1000;
		engine->rot_y += (double)(engine->mouse_x - x) / 1000;
		engine->rot_z += (double)(engine->mouse_y - y) / 1000
			+ (double)(engine->mouse_x - x) / 1000;
	}
	else if (engine->set_by == Button1)
	{
		mouse_vec = vec3_from_points((t_vec3){engine->mouse_x, engine->mouse_y,
				0}, (t_vec3){x, y, 0});
		printf("x: %f, y: %f\n", mouse_vec.x, mouse_vec.y);
		engine->offset_x += 10 * mouse_vec.x;
		engine->offset_y += 10 * mouse_vec.y;
	}
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
	head = map_nodes(argv[1]);
	if (!head)
		return (1);
	if (!engine_init(head))
		return (1);
	current = head;
	while (current)
	{
		current->coords.z *= -0.1;
		current = current->next;
	}
	mlx_hook(engine->win, ButtonPress, ButtonPressMask, &mouse_pressed, engine);
	mlx_hook(engine->win, MotionNotify, Button1MotionMask | Button3MotionMask,
		&transform_view, engine);
	mlx_loop_hook(engine->mlx, &draw_loop, head);
	mlx_key_hook(engine->win, &key_press, engine);
	mlx_loop(engine->mlx);
	return (0);
}
