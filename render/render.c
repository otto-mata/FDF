/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:45:15 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/19 05:22:05 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>

long long	timeInMilliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

int	key_press(int keycode)
{
	t_engine		*engine;
	static double	offset = 0.5;

	engine = engine_instance();
	if (!engine)
		return (1);
	printf("key: %d\n", keycode);
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
		offset += 0.5;
	if (keycode == 65453)
		offset -= 0.5;
	return (0);
}

int	draw_loop(t_grid_node *node) // 70 32 12
{
	int color;
	int i;
	t_grid_node *head;
	t_engine *engine;
	char s_x[64];
	char s_y[64];
	char s_z[64];

	engine = engine_instance();
	if (!engine)
		return (1);
	head = node;
	sprintf(s_x, "rot_x: %.2f", engine->rot_x);
	sprintf(s_y, "rot_y: %.2f", engine->rot_y);
	sprintf(s_z, "rot_z: %.2f", engine->rot_z);
	mlx_string_put(engine->mlx, engine->win, 5, 10, 0xffffffff, s_x);
	mlx_string_put(engine->mlx, engine->win, 5, 25, 0xffffffff, s_y);
	mlx_string_put(engine->mlx, engine->win, 5, 40, 0xffffffff, s_z);
	if (timeInMilliseconds() - engine->t < 16)
	{
		return (0);
	}
	mlx_clear_window(engine->mlx, engine->win);
	while (node)
	{
		i = 0;
		color = node->color > 0 ? node->color : 0xffffff;
		draw(node->coords.x, node->coords.y, node->coords.z, color);
		while (node && node->neighbors && node->neighbors[i])
		{
			gs_line(node->coords, node->neighbors[i]->coords);
			i++;
		}
		node = node->next;
	}
	// engine->rot_y += 0.5;
	// exit(0);
	engine->t = timeInMilliseconds();
	return (0);
}

int	main(void)
{
	t_engine	*engine;
	t_grid_node	*head;
	t_grid_node	*current;

	engine = engine_instance();
	if (!engine)
		return (1);
	if (!engine_init())
		return (1);
	engine->t = timeInMilliseconds();
	head = map_nodes();
	if (!head)
		return (1);
	current = head;
	while (current)
	{
		current->coords.x *= 20;
		current->coords.y *= 20;
		current->coords.z *= -10;
		current = current->next;
	}
	engine->rot_x = 70;
	engine->rot_y = 32;
	engine->rot_z = 12;
	mlx_loop_hook(engine->mlx, &draw_loop, head);
	mlx_key_hook(engine->win, &key_press, 0);
	mlx_loop(engine->mlx);
	return (0);
}
