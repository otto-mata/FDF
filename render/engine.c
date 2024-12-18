/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:13:59 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/17 23:40:32 by tblochet         ###   ########.fr       */
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
		engine->config.height = HEIGHT;
		engine->config.width = WIDTH;
		engine->config.title = TITLE;
	}
	return (engine);
}

bool	engine_init(void)
{
	t_engine	*engine;

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
	free(engine->mlx);
	free(engine);
	return (true);
}
