/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:13:59 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/20 19:04:09 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	hook_close(void)
{
	if (engine_exit())
		exit(0);
	exit(1);
}

t_engine	*engine_instance(void)
{
	static t_engine	*engine = 0;

	if (!engine)
	{
		engine = malloc(sizeof(t_engine));
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

bool	engine_init(void)
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
	img->content = mlx_new_image(engine->mlx, engine->config.width,
			engine->config.height);
	if (!img->content)
		return (engine_exit());
	img->addr = mlx_get_data_addr(img->content, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	engine->img = img;
	set_crosshair();
	mlx_hook(engine->win, DestroyNotify, ButtonPressMask, &hook_close, 0);
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
	mlx_destroy_image(engine->mlx, engine->img->addr);
	free(engine->mlx);
	free(engine->img);
	free(engine);
	return (true);
}
