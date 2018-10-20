#include "parser.h"
#include "libft_adv.h"

static void		parser_set_fract(t_env *env, void (*set)(t_env *))
{
	set(env);
	env->param.z_ref = env->param.zoom;
	env->param.origin[0] = env->param.offset[0];
	env->param.origin[1] = env->param.offset[1];
	env->param.nb_iter = NB_ITER;
}

int				parse_arg(char *argv, t_env *env)
{
	int				i;
	static t_pars	fract[NB_FRACT] = {{MAND, mandelbrot_parser}
		, {JULIA, julia_parser}, {BURN, burningship_parser}};

	i = 0;
	while (i < NB_FRACT && ft_strcmp(argv, fract[i].id))
		i++;
	if (i == NB_FRACT)
		return (1);
	parser_set_fract(env, fract[i].set);
	return (0);
}
