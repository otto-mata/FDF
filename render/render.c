/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:45:15 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/20 19:35:19 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>

static void	draw_nodes(t_grid_node *node) __attribute__((hot));
int			draw_loop(t_grid_node *node) __attribute__((hot));
void		view_angle_DBG(void) __attribute__((hot));

int	key_press(int keycode)
{
	t_engine		*engine;
	static double	offset = 0.5;

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
	t_engine	*engine;
	int			color;
	int			i;

	engine = engine_instance();
	if (!engine)
		return ;
	while (node)
	{
		i = 0;
		color = node->color > 0 ? node->color : 0xffffff;
		while (node && node->neighbors && node->neighbors[i])
		{
			gs_line(node, node->neighbors[i]);
			i++;
		}
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
	while (i < (engine->img->line_length / 4) * engine->config.height)
	{
		image[i] = 0x000000;
		i++;
	}
}

int	draw_loop(t_grid_node *node)
{
	t_engine	*engine;

	// BENCHMARK_START();
	engine = engine_instance();
	if (!engine)
		return (1);
	clear_image();
	draw_nodes(node);
	draw_nodes(engine->crosshair);
	view_angle_DBG();
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->content, 0,
		0);
	// engine->rot_y += 0.05;
	// engine->rot_x += 0.02;
	// engine->rot_z -= 0.02;
	// BENCHMARK_END();
	return (0);
}

t_vec3	apply_projection(t_grid_node *p)
{
	t_vec3		v;
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		exit(EXIT_FAILURE);
	v.x = p->coords.x;
	v.y = p->coords.y;
	v.z = p->coords.z;
	rot_x(&v.y, &v.z, engine->rot_x);
	rot_y(&v.x, &v.z, engine->rot_y);
	rot_z(&v.x, &v.y, engine->rot_z);
	v.z = 0;
	return (v);
}

void	view_angle_DBG(void)
{
	t_vec3		xyz[3];
	double		theta[3];
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		exit(EXIT_FAILURE);
	xyz[0] = apply_projection(engine->crosshair->neighbors[0]);
	xyz[1] = apply_projection(engine->crosshair->neighbors[1]);
	xyz[2] = apply_projection(engine->crosshair->neighbors[2]);
	theta[0] = acos(vec3_dot(&xyz[0], &xyz[1]) / (vec3_len(&xyz[0])
				* vec3_len(&xyz[1]))) * (180 / PI);
	theta[1] = acos(vec3_dot(&xyz[1], &xyz[2]) / (vec3_len(&xyz[1])
				* vec3_len(&xyz[2]))) * (180 / PI);
	theta[2] = acos(vec3_dot(&xyz[2], &xyz[0]) / (vec3_len(&xyz[2])
				* vec3_len(&xyz[0]))) * (180 / PI);
	printf("\rrX: %.3f, rY: %.3f, rZ: %.3f", engine->rot_x, engine->rot_y,
		engine->rot_z);
	printf(", ANGLES: %.3f, %.3f, %.3f\r", theta[0], theta[1], theta[2]);
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
		current->coords.z *= -3;
		current = current->next;
	}
	engine->rot_x = 45;
	engine->rot_y = 35.264;
	engine->rot_z = 28.264;
	mlx_loop_hook(engine->mlx, &draw_loop, head);
	mlx_key_hook(engine->win, &key_press, 0);
	mlx_loop(engine->mlx);
	return (0);
}
