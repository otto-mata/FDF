/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   render.h                                             ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/17 22:53:23 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:42:30 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "../fdf/readerv2/readerv2.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../vec3/vec3.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/extensions/XShm.h>
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
# define MAX_EVENT 36
# include <time.h>

# define BENCHMARK_START() clock_t start_time = clock();

# define BENCHMARK_END()                                                   \
	clock_t end_time = clock();                                           \
	double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC; \
	printf("%.12f\n", time_spent);

typedef struct s_engine			t_engine;
typedef struct s_ngin_conf		t_ngin_conf;
typedef struct s_image			t_image;
typedef struct s_mlx_event_list	t_mlx_event_list;
typedef struct s_mlx_win_list	t_mlx_win_list;
typedef struct s_mlx			t_mlx;

struct							s_ngin_conf
{
	int							width;
	int							height;
	char						*title;
};

struct							s_engine
{
	t_mlx						*mlx;
	t_mlx_win_list				*win;
	double						rot_x;
	double						rot_y;
	double						rot_z;
	double						zoom;
	t_image						*img;
	t_ngin_conf					config;
	t_vec3						origin[3];
	int							mouse_x;
	int							mouse_y;
	int							offset_x;
	int							offset_y;
	int							set_by;
	double						frametime;
	char						*fname;
};

struct							s_image
{
	XImage						*image;
	Pixmap						pix;
	GC							gc;
	int							bpp;
	int							line_length;
	int							width;
	int							height;
	int							type;
	int							format;
	char						*data;
	XShmSegmentInfo				shm;
};

struct							s_mlx_event_list
{
	int							mask;
	int							(*hook)();
	void						*param;
};

struct							s_mlx_win_list
{
	Window						window;
	GC							gc;
	struct s_win_list			*next;
	int							(*mouse_hook)();
	int							(*key_hook)();
	int							(*expose_hook)();
	void						*mouse_param;
	void						*key_param;
	void						*expose_param;
	t_mlx_event_list			hooks[MAX_EVENT];
};

struct							s_mlx
{
	Display						*display;
	Window						root;
	int							screen;
	int							depth;
	Visual						*visual;
	Colormap					cmap;
	int							private_cmap;
	t_mlx_win_list				*win_list;
	int							(*loop_hook)();
	void						*loop_param;
	int							use_xshm;
	int							pshm_format;
	int							do_flush;
	int							decrgb[6];
	Atom						wm_delete_window;
	Atom						wm_protocols;
	int							end_loop;
};

int								engine_init(t_grid_node *nodes, char *fname);
t_engine						*engine_instance(void);
void							engine_exit(void) __attribute__((noreturn));

int								draw(t_grid_node p) __attribute__((hot));
int								gs_line(t_grid_node *p1, t_grid_node *p2);
void							rot_x(double *y, double *z, double x_angle);
void							rot_y(double *x, double *z, double y_angle);
void							rot_z(double *x, double *y, double z_angle);
void							set_crosshair(void);
t_vec3							apply_projection(t_grid_node *p);
#endif
