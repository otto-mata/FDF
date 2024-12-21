/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:53:23 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/21 16:57:49 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "../fdf/reader/reader.h"
# include "../mlx/mlx.h"
# include "../vec3/vec3.h"
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
# define PI 3.141592653589793238462643383279502884197169399375105820974944592307
# define RAD_DEG_RATIO 57.29577951308232
# define DEG_RAD_RATIO 0.017453292519943295

# include <time.h>

# define BENCHMARK_START() clock_t start_time = clock();

# define BENCHMARK_END()                                                   \
	clock_t end_time = clock();                                           \
	double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC; \
	printf("%.12f\n", time_spent);

typedef struct s_engine		t_engine;
typedef struct s_ngin_conf	t_ngin_conf;
typedef struct s_image		t_image;
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
	double					rot_x;
	double					rot_y;
	double					rot_z;
	double					zoom;
	t_image					*img;
	t_ngin_conf				config;
	t_vec3					origin[3];
	bool					to_update;
};

struct						s_image
{
	void					*content;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
};

bool						engine_init(void);
t_engine					*engine_instance(void);
bool						engine_exit(void);

bool						draw(t_grid_node p) __attribute__((hot));
bool						gs_line(t_grid_node *p1, t_grid_node *p2);
void						rot_x(double *y, double *z, double x_angle);
void						rot_y(double *x, double *z, double y_angle);
void						rot_z(double *x, double *y, double z_angle);
void						set_crosshair(void);
t_vec3						apply_projection(t_grid_node *p);
#endif