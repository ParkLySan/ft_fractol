#ifndef PARSER_H
# define PARSER_H
# define NB_FRACT     3

# include "fractol.h"

typedef struct	s_pars
{
	char	*id;
	void	(*set)(t_env *);
}				t_pars;

void			mandelbrot_parser(t_env *env);
void			julia_parser(t_env *env);
void			burningship_parser(t_env *env);

#endif
