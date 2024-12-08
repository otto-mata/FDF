#include <math.h>

struct					s_point2
{
	double				x;
	double				y;
};
typedef struct s_point2	t_point2;

void					draw(int x, int y);

static void	plot_low_increment(int *d, int dy_dx, int *y, int yi)
{
	int	dx;
	int	dy;

	dx = dy_dx >> 16;
	dy = dy_dx & 0xFFFF;
	if (*d > 0)
	{
		*y += yi;
		*d -= (2 * dx);
	}
	*d += (2 * dy);
}

static void	plot_high_increment(int *d, int dx_dy, int *x, int xi)
{
	int	dx;
	int	dy;

	dx = dx_dy >> 16;
	dy = dx_dy & 0xFFFF;
	if (*d > 0)
	{
		*x += xi;
		*d -= (2 * dy);
	}
	*d += (2 * dx);
}

static void	plot_line_low(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	x;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	else
	{
		yi = 1;
	}
	d = (2 * dy) - dx;
	x = x0;
	while (x <= x1)
	{
		draw(x, y0);
		plot_low_increment(&d, (dx << 16) | dy, &y0, yi);
		x++;
	}
}

static void	plot_line_high(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	y;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	else
	{
		xi = 1;
	}
	d = (2 * dx) - dy;
	y = y0;
	while (y <= y1)
	{
		draw(x0, y);
		plot_high_increment(&d, (dx << 16) | dy, &x0, xi);
		y++;
	}
}

void	bresenham_line(t_point2 *a, t_point2 *b)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	x0 = (int)round(a->x);
	y0 = (int)round(a->y);
	x1 = (int)round(b->x);
	y1 = (int)round(b->y);
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			plot_line_low(x1, y1, x0, y0);
		else
			plot_line_low(x0, y0, x1, y1);
	}
	else
	{
		if (y0 > y1)
			plot_line_high(x1, y1, x0, y0);
		else
			plot_line_high(x0, y0, x1, y1);
	}
}
