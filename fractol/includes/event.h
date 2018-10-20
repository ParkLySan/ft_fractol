#ifndef EVENT_H
# define EVENT_H

# include <limits.h>

# define KEY_ESC          53
# define KEY_SPACE        49
# define KEY_LEFT         123
# define KEY_RIGHT        124
# define KEY_UP           126
# define KEY_DOWN         125
# define KEY_MINUS        78
# define KEY_PLUS         69
# define KEY_ENTR         76

# define SCROLL_UP        4
# define SCROLL_DOWN      5

# define INPUT_LEFT       0b00000001
# define INPUT_RIGHT      0b00000010
# define INPUT_UP         0b00000100
# define INPUT_DOWN       0b00001000
# define INPUT_PLUS       0b00010000
# define INPUT_MINUS      0b00100000
# define INPUT_MOUSE      0b01000000
# define INPUT_SCROLL     0b10000000

# define MV_SPEED         10
# define SCROLL_SPEED     0.10
# define ITER_SPEED       0.10

# define ITER_MAX         5000
# define ITER_MIN         1

# define ZOOM_MAX         100000000000000
# define ZOOM_MIN         1

#endif
