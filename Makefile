CC = cc

NAME =	cub3d 

CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c parsing/parsing.c   parsing/help.c parsing/free.c parsing/utils.c parsing/check.c  parsing/get_next_line/get_next_line.c  parsing/get_next_line/get_next_line_utils.c parsing/color/color_parsing.c parsing/ft_split.c parsing/color/check_line.c parsing/map_parsing.c   parsing/path/dire_parsing.c parsing/path/check2.c parsing/path/help.c execution/cub3d.c 

OBJS = $(SRCS:.c=.o)

MLX_DIR = /usr/include/minilibx-linux

MLX =  -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all clean
