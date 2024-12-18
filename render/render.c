/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:45:15 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/18 01:15:27 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	draw_square(t_ipoint square[4])
{
	for (size_t i = 0; i < 4; i++)
	{
		draw(square[i].x, square[i].y, 0xffffffff);
	}
	return (true);
}

int	main(void)
{
	t_engine	*engine;
	t_ipoint	square[4];

	engine = engine_instance();
	if (!engine)
		return (1);
	if (!engine_init())
		return (1);
	square[0] = (t_ipoint){engine->config.width / 2 - 20, engine->config.height
		/ 2 - 20, 0};
	square[1] = (t_ipoint){engine->config.width / 2 + 20, engine->config.height
		/ 2 - 20, 0};
	square[2] = (t_ipoint){engine->config.width / 2 + 20, engine->config.height
		/ 2 + 20, 0};
	square[3] = (t_ipoint){engine->config.width / 2 - 20, engine->config.height
		/ 2 + 20, 0};
	for (size_t i = 0; i < 4; i++)
	{
		rot_x(&square[i].x, &square[i].z, -0.615472907);
		rot_y(&square[i].x, &square[i].z, -0.523599);
		rot_z(&square[i].x, &square[i].y, 0.615472907);
		square[i].x += WIDTH / 2;
		square[i].y -= HEIGHT / 8;
	}
	
	draw_square(square);
	// gs_line(square[0], square[1]);
	gs_line(square[1], square[2]);
	// gs_line(square[2], square[3]);
	// gs_line(square[3], square[0]);
	mlx_loop(engine->mlx);
	return (0);
}
