#include "event.h"
#include "mlx.h"
#include "fractol.h"
#include <math.h>

int			event_key_pressed(int key, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (key == KEY_ESC)
		return (fract_quit(&(env->mlx), 0));
	if (key == KEY_SPACE)
	{
		env->param.zoom = env->param.z_ref;
		env->param.offset[0] = env->param.origin[0];
		env->param.offset[1] = env->param.origin[1];
		env->param.nb_iter = NB_ITER;
		env->keys_flag = env->keys_flag | INPUT_SCROLL;
	}
	else if (key == KEY_ENTR)
		env->keys_flag = (env->keys_flag & ~INPUT_MOUSE)
			| (~(env->keys_flag) & INPUT_MOUSE);
	else
		env->keys_flag = env->keys_flag
			| (key == KEY_LEFT) * INPUT_LEFT
			| (key == KEY_RIGHT) * INPUT_RIGHT
			| (key == KEY_UP) * INPUT_UP
			| (key == KEY_DOWN) * INPUT_DOWN
			| (key == KEY_MINUS) * INPUT_MINUS
			| (key == KEY_PLUS) * INPUT_PLUS;
	return (0);
}

int			event_key_released(int key, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->keys_flag = env->keys_flag
		& ~((key == KEY_LEFT) * INPUT_LEFT)
		& ~((key == KEY_RIGHT) * INPUT_RIGHT)
		& ~((key == KEY_UP) * INPUT_UP)
		& ~((key == KEY_DOWN) * INPUT_DOWN)
		& ~((key == KEY_MINUS) * INPUT_MINUS)
		& ~((key == KEY_PLUS) * INPUT_PLUS);
	return (0);
}

int			event_button_pressed(int button, int x, int y, void *arg)
{
	double		offset;
	t_env		*env;
	t_param		*param;

	env = (t_env *)arg;
	param = &(env->param);
	if (button == SCROLL_UP && param->zoom < ZOOM_MAX)
	{
		offset = fmin((ZOOM_MAX - param->zoom) / param->zoom, SCROLL_SPEED);
		param->zoom += param->zoom * offset;
		param->offset[0] += x / param->zoom * offset;
		param->offset[1] += y / param->zoom * offset;
		env->keys_flag = env->keys_flag | INPUT_SCROLL;
	}
	else if (button == SCROLL_DOWN && param->zoom > ZOOM_MIN)
	{
		offset = fmin((param->zoom - ZOOM_MIN) / param->zoom, SCROLL_SPEED);
		param->zoom -= param->zoom * offset;
		param->offset[0] -= x / param->zoom * offset;
		param->offset[1] -= y / param->zoom * offset;
		env->keys_flag = env->keys_flag | INPUT_SCROLL;
	}
	return (0);
}

int			event_mouse(int x, int y, void *arg)
{
	t_param		*param;

	if (((t_env *)arg)->keys_flag & INPUT_MOUSE
			&& x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		param = &((t_env*)arg)->param;
		param->mouse[0] = ((double)x - WIDTH / 2) / (WIDTH / 2);
		param->mouse[1] = ((double)y - HEIGHT / 2) / (HEIGHT / 2);
	}
	return (0);
}

int			event_loop_hook(void *param)
{
	t_env		*env;

	env = (t_env *)param;
	if (env->keys_flag)
	{
		if (env->keys_flag & INPUT_RIGHT)
			env->param.offset[0] -= MV_SPEED / env->param.zoom;
		if (env->keys_flag & INPUT_LEFT)
			env->param.offset[0] += MV_SPEED / env->param.zoom;
		if (env->keys_flag & INPUT_UP)
			env->param.offset[1] += MV_SPEED / env->param.zoom;
		if (env->keys_flag & INPUT_DOWN)
			env->param.offset[1] -= MV_SPEED / env->param.zoom;
		if (env->keys_flag & INPUT_MINUS && env->param.nb_iter > ITER_MIN)
			env->param.nb_iter -= fmax(1, env->param.nb_iter * ITER_SPEED);
		if (env->keys_flag & INPUT_PLUS && env->param.nb_iter < ITER_MAX)
			env->param.nb_iter += fmax(1, env->param.nb_iter * ITER_SPEED);
		if (env->keys_flag & INPUT_SCROLL)
			env->keys_flag = env->keys_flag & ~INPUT_SCROLL;
		if (fract_draw(env->img.pixel, &(env->param), env->fun, &(env->mlx)))
			fract_quit(param, 1);
		hud_draw(&(env->param), &(env->mlx));
	}
	return (0);
}
