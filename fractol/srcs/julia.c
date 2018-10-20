#include "color.h"
#include "fractol.h"
#include "thread.h"

static int		julia_pixel(int nb_iter, double z[2], double c_r, double c_i)
{
	double		z_sqr[2];
	int			i;

	z_sqr[0] = z[0] * z[0];
	z_sqr[1] = z[1] * z[1];
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

static void		*julia_thread(void *param)
{
	t_args	*thr_arg;
	int		i;
	int		stop;
	double	z[2];

	thr_arg = (t_args *)param;
	i = thr_arg->index * WIDTH * HEIGHT / NUM_THREAD;
	stop = (thr_arg->index + 1) * WIDTH * HEIGHT / NUM_THREAD;
	while (i < stop)
	{
		z[0] = i % WIDTH / thr_arg->zoom + thr_arg->offset_x;
		z[1] = i / WIDTH / thr_arg->zoom + thr_arg->offset_y;
		thr_arg->pixel[i] =
			julia_pixel(thr_arg->nb_iter, z,
					thr_arg->mouse_x, thr_arg->mouse_y);
		i++;
	}
	return (NULL);
}

void			julia_parser(t_env *env)
{
	env->param.zoom = JULIA_ZOOM;
	env->param.offset[0] = JULIA_X;
	env->param.offset[1] = JULIA_Y;
	env->param.mouse[0] = 0.285;
	env->param.mouse[1] = 0.01;
	env->fun = julia_thread;
}
