#include "color.h"
#include "fractol.h"
#include "thread.h"

static int		mandelbrot_pixel(int nb_iter, double c_r, double c_i)
{
	double		z[2];
	double		z_sqr[2];
	int			i;

	z[0] = 0;
	z[1] = 0;
	z_sqr[0] = 0;
	z_sqr[1] = 0;
	i = -1;
	while (++i < nb_iter && (z_sqr[0] + z_sqr[1]) <= 4)
	{
		z[1] = (z[0] + z[1]) * (z[0] + z[1]) - z_sqr[0] - z_sqr[1] + c_i;
		z[0] = z_sqr[0] - z_sqr[1] + c_r;
		z_sqr[0] = z[0] * z[0];
		z_sqr[1] = z[1] * z[1];
	}
	if (i == nb_iter)
		return (BLACK);
	else
		return (color_gradient(i));
}

static void		*mandelbrot_thread(void *param)
{
	t_args	*thr_arg;
	int		i;
	int		stop;

	thr_arg = (t_args *)param;
	i = thr_arg->index * WIDTH * HEIGHT / NUM_THREAD;
	stop = (thr_arg->index + 1) * WIDTH * HEIGHT / NUM_THREAD;
	while (i < stop)
	{
		thr_arg->pixel[i] =
			mandelbrot_pixel(thr_arg->nb_iter,
					i % WIDTH / thr_arg->zoom + thr_arg->offset_x,
					i / WIDTH / thr_arg->zoom + thr_arg->offset_y);
		i++;
	}
	return (NULL);
}

void			mandelbrot_parser(t_env *env)
{
	env->param.zoom = MAND_ZOOM;
	env->param.offset[0] = MAND_X;
	env->param.offset[1] = MAND_Y;
	env->fun = mandelbrot_thread;
}
