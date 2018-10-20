.PHONY: all clean fclean re dclean

NAME = fractol
CC = clang
CFLAGS = -Wall -Wextra -Werror

SRCS_FILES = fractol.c    \
			 parser.c     \
			 threads.c    \
			 hud.c        \
			 event_hook.c \
			 color.c      \
			 mandelbrot.c \
			 julia.c      \
			 burningship.c
OBJS_FILES = $(SRCS_FILES:.c=.o)
DPDS_FILES = $(SRCS_FILES:.c=.d)

SRCS_DIR = srcs/
OBJS_DIR = objs/
DPDS_DIR = depends/

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_FILES))
DPDS = $(addprefix $(DPDS_DIR), $(DPDS_FILES))

LIB = ft_adv
LIB_DIR = libft/
LIB_A = $(LIB_DIR)lib$(LIB).a

MLX = mlx
MLX_DIR = mlx/
MLX_A = $(MLX_DIR)lib$(MLX).a

FWK = -framework OpenGL -framework Appkit

INC_LIB = -L./$(LIB_DIR) -l$(LIB) -L./$(MLX_DIR) -l$(MLX) $(FWK) -lm

HEADER = includes
INC = -I $(HEADER) -I $(LIB_DIR) -I $(MLX_DIR)

PREFIX = @printf "["$(GREEN)"$(NAME)"$(NC)"]"$(LBLUE)" - "$(NC)

NC = '\033[0m'
RED = '\033[0;31m'
LRED = '\033[1;31m'
LBLUE = '\033[1;34m'
GREEN = '\033[0;32m'
LGREEN = '\033[1;32m'
ORANGE = '\033[0;33m'
YELLOW = '\033[1;33m'

all: $(NAME)

$(NAME): $(MLX_A) $(LIB_A) $(OBJS)
	$(PREFIX)
	$(CC) $(CFLAGS) $(INC) $(INC_LIB) -o $(NAME) $(OBJS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(PREFIX)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $(@:$(OBJS_DIR)%.o=$(SRCS_DIR)%.c)

$(DPDS_DIR)%.d: $(SRCS_DIR)%.c
	$(PREFIX)
	$(CC) $(CFLAGS) $(INC) -MT $(@:$(DPDS_DIR)%.d=$(OBJS_DIR)%.o) -MM $^ > $@

$(LIB_A):
	@make -C $(LIB_DIR) all

$(MLX_A):
	@make -C $(MLX_DIR) all

clean: dclean
	@make -C $(MLX_DIR) clean
	@make -C $(LIB_DIR) clean
	$(PREFIX)
	rm -f $(OBJS)

fclean: dclean
	@make -C $(MLX_DIR) clean
	@make -C $(LIB_DIR) fclean
	$(PREFIX)
	rm -f $(OBJS)
	$(PREFIX)
	rm -f $(NAME)

re:
	@make fclean
	@make all

dclean:
	$(PREFIX)
	rm -f $(DPDS)

-include $(DPDS)
