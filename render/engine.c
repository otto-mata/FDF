/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:13:59 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/27 12:26:02 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	hook_close(t_grid_node *nodes)
{
	t_grid_node	*next;

	ft_printf("\n");
	while (nodes)
	{
		next = nodes->next;
		if (nodes->next == 0)
			free(nodes->map_dim);
		free(nodes->neighbors);
		free(nodes);
		nodes = next;
	}
	engine_exit();
	return (0);
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
		engine->zoom = 2;
		engine->rot_x = 45;
		engine->rot_y = 35.264;
		engine->rot_z = 28.264;
		engine->mouse_x = 0;
		engine->mouse_y = 0;
		engine->config.height = HEIGHT;
		engine->config.width = WIDTH;
		engine->config.title = TITLE;
	}
	return (engine);
}

bool	engine_init(t_grid_node *nodes, char *fname)
{
	t_engine	*engine;
	t_image		*img;

	engine = engine_instance();
	if (!engine)
		return (false);
	engine->fname = fname;
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
		engine_exit();
	img->data = mlx_get_data_addr(img->image, &img->bpp, &img->line_length,
			&img->image->byte_order);
	engine->img = img;
	set_crosshair();
	mlx_hook(engine->win, DestroyNotify, ButtonPressMask, &hook_close, nodes);
	return (true);
}

void	engine_exit(void)
{
	t_engine	*engine;

	engine = engine_instance();
	if (!engine)
		exit(EXIT_FAILURE);
	mlx_destroy_image(engine->mlx, engine->img->image);
	mlx_destroy_window(engine->mlx, engine->win);
	mlx_destroy_display(engine->mlx);
	free(engine->mlx);
	free(engine->img);
	free(engine);
	exit(EXIT_SUCCESS);
}
