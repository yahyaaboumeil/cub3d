CC = cc -g
NAME = cub3d 
CFLAGS = -Wall -Wextra -Werror 
SRCS = main.c parsing/parsing.c parsing/utils.c parsing/check.c parsing/dire_parsing.c parsing/get_next_line/get_next_line.c  parsing/get_next_line/get_next_line_utils.c parsing/color/color_parsing.c parsing/color/ft_split.c parsing/color/check_line.c parsing/map_parsing.c


OBJS = $(SRCS:.c=.o)

# MLX_DIR = /usr/include/minilibx-linux
# MLX = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_DIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all