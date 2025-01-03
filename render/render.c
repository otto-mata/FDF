/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   render.c                                             ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/17 22:45:15 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/03 02:34:27 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>
#include <math.h>

static void			draw_nodes(t_grid_node *node) __attribute__((hot));
int					draw_loop(t_grid_node *node) __attribute__((hot));

void	send_destroy_notify(Display *dpy, Window target)
{
	XEvent	event;

	ft_memset(&event, 0, sizeof(event));
	event.xdestroywindow.type = DestroyNotify;
	event.xdestroywindow.serial = 0;
	event.xdestroywindow.send_event = True;
	event.xdestroywindow.display = dpy;
	event.xdestroywindow.event = target;
	event.xdestroywindow.window = target;
	XSendEvent(dpy, target, False, NoEventMask, &event);
	XFlush(dpy);
}

int	key_press(int keycode, t_engine *engine)
{
	static int	proj = 1;

	if (keycode == XK_Escape || keycode == 'q')
		send_destroy_notify(engine->mlx->display, engine->win->window);
	else if (keycode == 'p')
	{
		proj ^= 1;
		if (proj)
		{
			engine->rot_x = 45;
			engine->rot_y = 35.264;
			engine->rot_z = 28.264;
		}
		else
		{
			engine->rot_x = 68.4;
			engine->rot_y = 43.05;
			engine->rot_z = 14.5;
		}
	}
	else if (keycode == 'r')
	{
		engine->rot_x = 45;
		engine->rot_y = 35.264;
		engine->rot_z = 28.264;
		proj = 1;
	}
	return (0);
}

static void	draw_nodes(t_grid_node *node)
{
	while (node)
	{
		if (node->n_neighbors >= 1)
			gs_line(node, node->neighbors[0]);
		if (node->n_neighbors == 2)
			gs_line(node, node->neighbors[1]);
		node = node->next;
	}
}

struct				s_256bits
{
	long			a;
	long			b;
	long			c;
	long			d;
};

struct s_256bits	zero256(void)
{
	const struct s_256bits	pad = {0, 0, 0, 0};

	return (pad);
}

void	clear_image(void)
{
	struct s_256bits	*image;
	int					i;
	t_engine			*engine;

	engine = engine_instance();
	if (!engine)
		return ;
	image = (struct s_256bits *)engine->img->data;
	i = 0;
	while (i < (engine->img->line_length >> 5) * engine->config.height)
	{
		image[i] = zero256();
		i++;
	}
}

static void	clamp_rotations(t_engine *engine)
{
	return ;
	if (engine->rot_x > 360)
		engine->rot_x -= 360;
	else if (engine->rot_x < -360)
		engine->rot_x += 360;
	if (engine->rot_y > 360)
		engine->rot_y -= 360;
	else if (engine->rot_y < -360)
		engine->rot_y += 360;
	if (engine->rot_z > 360)
		engine->rot_z -= 360;
	else if (engine->rot_z < -360)
		engine->rot_z += 360;
}

int	draw_loop(t_grid_node *node)
{
	t_engine	*engine;
	clock_t		start_time;

	start_time = clock();
	engine = engine_instance();
	if (!engine)
		return (1);
	clamp_rotations(engine);
	clear_image();
	set_crosshair();
	draw_nodes(node);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->img->image, 0, 0);
	engine->frametime = (double)(clock() - start_time) / ((__clock_t)1000);
	setbuf(stdout, 0);
	ft_printf("\rframetime: ~%dms | FPS: ~%d       ",
		(int)__builtin_round(engine->frametime), (int)__builtin_round(1000
			/ (engine->frametime)));
	return (0);
}

int	mouse_pressed(int button, int x, int y, t_engine *engine)
{
	if (button == Button3 || button == Button1)
	{
		engine->mouse_x = x;
		engine->mouse_y = y;
		engine->set_by = button;
	}
	else if (button == Button4)
		engine->zoom += 0.2;
	else if (button == Button5)
		engine->zoom -= 0.2;
	return (0);
}

t_vec3	vec3_from_points(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = (double)(b.x - a.x) / (double)b.x;
	v.y = (double)(b.y - a.y) / (double)b.y;
	if (v.x > 1)
		v.x = 1;
	if (v.x < -1)
		v.x = -1;
	if (v.y > 1)
		v.y = 1;
	if (v.y < -1)
		v.y = -1;
	return (v);
}

int	transform_view(int x, int y, t_engine *engine)
{
	const t_vec3	p_center = {WIDTH / 2,HEIGHT / 2, 0};
	t_vec3			mouse_vec;
	t_vec3			p_mouse;

	if (engine->set_by == Button3)
	{
		engine->rot_x += (double)(engine->mouse_y - y) / 1000;
		engine->rot_y += (double)(engine->mouse_x - x) / 1000;
	}
	else if (engine->set_by == Button1)
	{
		engine->mouse_y = y;
		engine->mouse_x = x;
		p_mouse.x = x;
		p_mouse.y = y;
		p_mouse.z = 0;
		mouse_vec = vec3_from_points(p_center, p_mouse);
		engine->offset_x += 10 * mouse_vec.x;
		engine->offset_y += 10 * mouse_vec.y;
	}
	return (0);
}

int	usage(char *exec_name)
{
	ft_printf("Usage: %s <map_path> [cell_size] [z_scale]\n", exec_name);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_engine	*engine;
	t_map_data	*map;

	if (argc != 2)
		if (argc != 4)
			return (usage(argv[0]));
	engine = engine_instance();
	if (!engine)
		return (1);
	map = load_map(argv[1]);
	if (!map)
		return (1);
	if (!engine_init(map->nodes, argv[1]))
		return (1);
	while (map->iter)
	{
		map->iter->coords.z *= .2;
		map->iter = map->iter->next;
	}
	engine->rot_x = 0;
	engine->rot_y = 0;
	engine->rot_z = 0;
	mlx_hook(engine->win, ButtonPress, ButtonPressMask, &mouse_pressed, engine);
	mlx_hook(engine->win, MotionNotify, Button1MotionMask | Button3MotionMask,
		&transform_view, engine);
	mlx_loop_hook(engine->mlx, &draw_loop, map->nodes);
	mlx_key_hook(engine->win, &key_press, engine);
	mlx_loop(engine->mlx);
	return (0);
}
