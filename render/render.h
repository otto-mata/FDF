/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:53:23 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/20 11:27:56 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "../fdf/reader/reader.h"
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
# define PI 3.141592653589793238462643383279502884197169399375105820974944592307

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
};

struct						s_image
{
	void					*content;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
};

# ifndef STRUCT_POINT
#  define STRUCT_POINT

typedef struct s_point		t_point;
struct						s_point
{
	double					x;
	double					y;
	double					z;
};
# endif

bool						engine_init(void);
t_engine					*engine_instance(void);
bool						engine_exit(void);

bool						draw(t_grid_node p) __attribute__((hot));
bool						gs_line(t_grid_node *p1, t_grid_node *p2);
void						rot_x(double *y, double *z, double x_angle);
void						rot_y(double *x, double *z, double y_angle);
void						rot_z(double *x, double *y, double z_angle);
#endif