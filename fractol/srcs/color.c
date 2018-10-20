#include "color.h"

static double	color_set_limit(double dist, unsigned int color[2])
{
	if (dist < CAP_1)
	{
		color[0] = COL_COLD;
		color[1] = COL_LIGHT;
		return ((dist - 0) / (CAP_1 - 0));
	}
	else if (dist > CAP_2)
	{
		color[0] = COL_WARM;
		color[1] = COL_COLD;
		return ((dist - CAP_2) / (1 - CAP_2));
	}
	else
	{
		color[0] = COL_LIGHT;
		color[1] = COL_WARM;
		return ((dist - CAP_1) / (CAP_2 - CAP_1));
	}
}

unsigned int	color_gradient(double i)
{
	double			dist;
	unsigned int	rgb[3];
	unsigned int	color[2];

	dist = (double)((int)i % MOD) / MOD;
	dist = color_set_limit(dist, color);
	rgb[0] = ((color[0] & RED) >> RED_OFF) * (1 - dist)
		+ ((color[1] & RED) >> RED_OFF) * dist;
	rgb[1] = ((color[0] & GREEN) >> GREEN_OFF) * (1 - dist)
		+ ((color[1] & GREEN) >> GREEN_OFF) * dist;
	rgb[2] = (color[0] & BLUE) * (1 - dist) + (color[1] & BLUE) * dist;
	return ((rgb[0] << RED_OFF) + (rgb[1] << GREEN_OFF) + rgb[2]);
}
