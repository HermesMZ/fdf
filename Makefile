NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_LIBS = -Lminilibx-linux -lmlx_Linux -lm
X_LIBS = -lXext -lX11
SRCS_DIR = src
OBJS_DIR = objs
INCLUDES_DIR = includes
LIBFT_DIR = libft
LIBMLX_DIR = minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = $(LIBMLX_DIR)/libmlx_Linux.a

SRCS = \
	main.c \
	project.c \
	rainbow.c \
	debug_utils.c \
	colors.c \
	count.c \
	draw.c \
	draw_commands.c \
	fdf.c \
	hooks.c \
	init.c \
	keys.c \
	map.c \
	point.c \
	utils.c \
	setup_view.c \
	setup_view_utils.c \

SRCS_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_PATH:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INCLUDES = -I $(INCLUDES_DIR) -I $(LIBFT_DIR)/includes -I $(LIBMLX_DIR)

all: $(LIBFT) $(LIBMLX) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX) $(MLX_LIBS) $(X_LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIBFT):
	@echo "Construction de libft.a..."
	@$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX):
	@echo "Construction de libmlx.a..."
	@git clone https://github.com/42paris/minilibx-linux.git
	@$(MAKE) -C $(LIBMLX_DIR)	

clean:
	@echo "Nettoyage des fichiers objets..."
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Nettoyage de $(NAME) et de libft..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(LIBMLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re