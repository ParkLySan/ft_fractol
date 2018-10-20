#ifndef FRACTOL_H
# define FRACTOL_H

# define MAND         "mandelbrot"
# define MAND_ZOOM    300
# define MAND_X       -2.0
# define MAND_Y       -1.3

# define JULIA        "julia"
# define JULIA_ZOOM   300
# define JULIA_X      -1.4
# define JULIA_Y      -1.3

# define BURN         "burningship"
# define BURN_ZOOM    250
# define BURN_X       -2
# define BURN_Y       -1.8

# define WIDTH        810
# define HEIGHT       810

# define NB_ITER      100

typedef struct			s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
}						t_mlx;

typedef struct			s_img
{
	unsigned int		*pixel;
	int					bpp;
	int					line_size;
	int					endian;
}						t_img;

typedef struct			s_param
{
	double		zoom;
	double		z_ref;
	double		offset[2];
	double		origin[2];
	int			nb_iter;
	double		mouse[2];
}						t_param;

typedef struct			s_env
{
	t_mlx		mlx;
	t_img		img;
	t_param		param;
	int			keys_flag;
	void		*(*fun)(void *);
}						t_env;

int						event_key_pressed(int key, void *param);
int						event_key_released(int key, void *param);
int						event_button_pressed(int button, int x, int y,
		void *param);
int						event_mouse(int x, int y, void *param);
int						event_loop_hook(void *param);

void					hud_draw(t_param *par, t_mlx *mlx);

int						parse_arg(char *argv, t_env *env);

int						fract_quit(void *param, int ret);
int						fract_draw(unsigned int *pixel, t_param *param,
		void *fun(void *), t_mlx *mlx);

#endif
