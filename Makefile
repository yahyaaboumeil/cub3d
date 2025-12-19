NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

# 1. ADD ALL DIRECTORIES WHERE YOUR .C FILES LIVE
# I added 'libft/*.c' and 'gnl/*.c' - update these names to match your folders!
SRCS        = $(wildcard *.c) \
              $(wildcard parsing/*.c) \
              $(wildcard parsing/path/*.c) \
			  $(wildcard parsing/get_next_line/*.c) \
              $(wildcard parsing/color/*.c) \
              $(wildcard /*.c)

OBJS        = $(SRCS:.c=.o)

MLX_DIR     = /usr/include/minilibx-linux
# 2. ADD -I for every folder containing a .h file
INC         = -I. -I$(MLX_DIR) -Iparsing -Ilibft -Ignl

MLX         = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re