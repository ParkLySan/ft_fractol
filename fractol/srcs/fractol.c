#include "error.h"
#include "fractol.h"
#include "libft_adv.h"
#include "mlx.h"
#include "thread.h"
#include <stdlib.h>
#include <unistd.h>

int				fract_quit(void *param, int ret)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (mlx->img)
		mlx_destroy_image(mlx->ptr, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	free(mlx->ptr);
	exit(ret);
}

static int		fract_usage(char *path)
{
	ft_printf("Usage: %s < %s | %s | %s >\n",
			path, MAND, JULIA, BURN);
	return (1);
}

static int		fract_initmlx(t_mlx *mlx, t_img *img, char *title)
{
	mlx->win = NULL;
	mlx->img = NULL;
	if (!(mlx->ptr = mlx_init()))
	{
		ft_putendl_fd(ERR_MLX_P, STDERR_FILENO);
		return (1);
	}
	if (!(mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, title)))
	{
		ft_putendl_fd(ERR_MLX_W, STDERR_FILENO);
		return (fract_quit(mlx, 1));
	}
	if (!(mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT)))
	{
		ft_putendl_fd(ERR_MLX_I, STDERR_FILENO);
		return (fract_quit(mlx, 1));
	}
	img->pixel = (unsigned int *)mlx_get_data_addr(mlx->img, &(img->bpp),
			&(img->line_size), &(img->endian));
	return (0);
}

int				fract_draw(unsigned int *pixel, t_param *par,
		void *fun(void *), t_mlx *mlx)
{
	int			n_thread;
	int			err;
	pthread_t	thread[NUM_THREAD];
	t_args		thr_arg[NUM_THREAD];

	n_thread = -1;
	while (++n_thread < NUM_THREAD)
		thr_arg[n_thread] = (t_args){par->nb_iter, pixel, n_thread, par->zoom,
			par->offset[0], par->offset[1], par->mouse[0], par->mouse[1]};
	err = threads_start(thread, thr_arg, fun);
	if (err || threads_stop(thread, NUM_THREAD))
		return (1);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	return (0);
}

int				main(int argc, char *argv[])
{
	t_env		env;

	if (argc != 2 || parse_arg(argv[1], &env))
		return (fract_usage(argv[0]));
	if (fract_initmlx(&(env.mlx), &(env.img), argv[1]))
		return (1);
	if (fract_draw(env.img.pixel, &(env.param), env.fun, &(env.mlx)))
		fract_quit(&(env.mlx), 1);
	hud_draw(&(env.param), &(env.mlx));
	mlx_loop_hook(env.mlx.ptr, event_loop_hook, &env);
	mlx_hook(env.mlx.win, 2, (1L << 0), event_key_pressed, &env);
	mlx_hook(env.mlx.win, 3, (1L << 1), event_key_released, &env);
	mlx_hook(env.mlx.win, 4, (1L << 2), event_button_pressed, &env);
	mlx_hook(env.mlx.win, 6, (1L << 6), event_mouse, &env);
	mlx_hook(env.mlx.win, 17, 0, fract_quit, &env);
	mlx_loop(env.mlx.ptr);
	return (0);
}
