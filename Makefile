SRCS		=	main.c \
				map_gestion.c \
				map_check.c \
				map_utils.c \
				general_utils.c \
				game_utils.c \
				start_game.c \
				game.c \
				load_assets.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \

OBJS		=	$(SRCS:.c=.o)

LIBFT		=	Libft/libft.a

NAME		=	so_long

FLAGS		=	-Wall -Wextra -Werror -g3

MLX42		=	"/Users/ngalzand/goinfre/MLX42/libmlx42.a" -I include -lglfw -L "/Users/ngalzand/goinfre/.brew/opt/glfw/lib"

RM			=	rm -rf

.c.o:
			gcc $(FLAGS) -I include -I /Users/ngalzand/goinfre/MLX42/include -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) -C Libft
			gcc $(FLAGS) $(OBJS) $(LIBFT) $(MLX42) -o $(NAME)
clean:
			$(RM) $(OBJS)
			$(MAKE) -C Libft clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C Libft fclean

re:			fclean all

bonus:		$(NAME)

.PHONY:		all clean fclean re bonus
