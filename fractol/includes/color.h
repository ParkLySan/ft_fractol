#ifndef COLOR_H
# define COLOR_H

# define BLUE       0x000000ff
# define GREEN      0x0000ff00
# define RED        0x00ff0000
# define ALPHA      0xff000000
# define WHITE      0x00ffffff
# define BLACK      0x00000000

# define BLUE_OFF   0
# define GREEN_OFF  8
# define RED_OFF    16

# define COBALT     0x0047ab
# define ORANGE_BR  0xcc5500
# define CHOCOLATE  0xd2691e
# define COOL_BLACK 0x002e63
# define CRIMSON    0xdc143c

# define COL_COLD   COOL_BLACK
# define COL_LIGHT  WHITE
# define COL_WARM   CHOCOLATE

# define CAP_1      0.33
# define CAP_2      0.66
# define MOD        200

unsigned int	color_gradient(double i);

#endif
