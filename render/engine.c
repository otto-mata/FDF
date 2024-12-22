/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:13:59 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/22 02:31:57 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	hook_close(t_grid_node *nodes)
{
	t_grid_node	*next;
	printf("exiting\n");
	while (nodes)
	{
		next = nodes->next;
		if (nodes->next == 0)
			free(nodes->map_dim);
		free(nodes->neighbors);
		free(nodes);
		nodes = next;
	}
	if (engine_exit())
		exit(0);
	exit(1);
}

t_engine	*engine_instance(void)
{
	static t_engine	*engine = 0;

	if (!engine)
	{
		engine = calloc(1, sizeof(t_engine));
		if (!engine)
			return (0);
		engine->mlx = 0;
		engine->win = 0;
		engine->zoom = 10;
		engine->config.height = HEIGHT;
		engine->config.width = WIDTH;
		engine->config.title = TITLE;
	}
	return (engine);
}

bool	engine_init(t_grid_node *nodes)
{
	t_engine	*engine;
	t_image		*img;

	engine = engine_instance();
	if (!engine)
		return (false);
	engine->mlx = mlx_init();
	if (!engine->mlx)
		return (free(engine), false);
	engine->win = mlx_new_window(engine->mlx, engine->config.width,
			engine->config.height, engine->config.title);
	if (!engine->win)
		return (mlx_destroy_display(engine->mlx), free(engine), false);
	img = malloc(sizeof(t_image));
	img->image = mlx_new_image(engine->mlx, engine->config.width,
			engine->config.height);
	if (!img->image)
		return (engine_exit());
	img->data = mlx_get_data_addr(img->image, &img->bpp,
			&img->line_length, &img->image->byte_order);
	engine->img = img;
	set_crosshair();
	mlx_hook(engine->win, DestroyNotify, ButtonPressMask, &hook_close, nodes);
	return (true);
}

bool	engine_exit(void)
{
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		return (false);
	mlx_destroy_window(engine->mlx, engine->win);
	mlx_destroy_display(engine->mlx);
	XFree((char *)engine->img->image);
	free(engine->mlx);
	free(engine->img);
	free(engine);
	return (true);
}
