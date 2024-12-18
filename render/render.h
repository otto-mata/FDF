/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:53:23 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/18 01:11:04 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "../mlx/mlx.h"
# include "X11/X.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# ifndef WIDTH
#  define WIDTH 1280
# endif
# ifndef HEIGHT
#  define HEIGHT 720
# endif
# ifndef TITLE
#  define TITLE "MLX Rendering"
# endif

typedef struct s_engine		t_engine;
typedef struct s_ngin_conf	t_ngin_conf;
typedef struct s_ipoint		t_ipoint;
typedef struct s_fpoint		t_fpoint;

struct						s_ngin_conf
{
	int						width;
	int						height;
	char					*title;
};

struct						s_engine
{
	void					*mlx;
	void					*win;
	t_ngin_conf				config;
};

struct						s_ipoint
{
	int						x;
	int						y;
	int						z;
};

struct						s_fpoint
{
	float					x;
	float					y;
	float					z;
};

bool						engine_init(void);
t_engine					*engine_instance(void);
bool						engine_exit(void);

bool						draw(int x, int y, int color);
bool						gs_line(t_ipoint p1, t_ipoint p2);
void						rot_x(int *y, int *z, double x_angle);
void						rot_y(int *x, int *z, double y_angle);
void						rot_z(int *x, int *y, double z_angle);
#endif