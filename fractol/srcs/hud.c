#include "color.h"
#include "error.h"
#include "fractol.h"
#include "libft_adv.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

static void	hud_zoom(long z, t_mlx *mlx)
{
	char	*to_print;
	char	*zoom;

	if (!(zoom = ft_ltoa(z)))
	{
		ft_putendl_fd(ERR_MALLOC, STDERR_FILENO);
		fract_quit(mlx, 1);
	}
	if (!(to_print = ft_strnew(ft_strlen("zoom : ") + ft_strlen(zoom)
					+ ft_strlen(" pixels per unit"))))
	{
		ft_putendl_fd(ERR_MALLOC, STDERR_FILENO);
		free(zoom);
		fract_quit(mlx, 1);
	}
	ft_strcpy(to_print, "zoom : ");
	ft_strcat(to_print, zoom);
	free(zoom);
	ft_strcat(to_print, " pixels per unit");
	mlx_string_put(mlx->ptr, mlx->win, 25, 25, CRIMSON, to_print);
	free(to_print);
}

static void	hud_iter(int i, t_mlx *mlx)
{
	char	*to_print;
	char	*iter;

	if (!(iter = ft_itoa(i)))
	{
		ft_putendl_fd(ERR_MALLOC, STDERR_FILENO);
		fract_quit(mlx, 1);
	}
	if (!(to_print = ft_strnew(ft_strlen("iterations : ") + ft_strlen(iter))))
	{
		ft_putendl_fd(ERR_MALLOC, STDERR_FILENO);
		free(iter);
		fract_quit(mlx, 1);
	}
	ft_strcpy(to_print, "iterations : ");
	ft_strcat(to_print, iter);
	free(iter);
	mlx_string_put(mlx->ptr, mlx->win, 25, 50, CRIMSON, to_print);
	free(to_print);
}

void		hud_draw(t_param *par, t_mlx *mlx)
{
	hud_zoom((long)(par->zoom), mlx);
	hud_iter(par->nb_iter, mlx);
}
