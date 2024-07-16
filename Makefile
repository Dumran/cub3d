CC					= clang
CFLAGS			=
PROGRAM			= cub3d
SRC_DIR			= src
CMD_DIR			= cmd
BUILD_DIR		= build
BIN_DIR			= $(BUILD_DIR)/bin
INC_DIR			= -Iinc -I$(MLX_DIR) -I$(LIBFT_DIR)
NAME				= $(BIN_DIR)/$(PROGRAM)
SRCS				= src/err.c src/init.c src/util.c src/hook_move.c src/hook.c \
							src/map_meta.c src/map_validate.c src/map.c src/render.c
OBJS				= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
CMD					= $(CMD_DIR)/$(PROGRAM).c
RM					= rm -rf

MLX_DIR			= lib/libmlx
MLX					= $(MLX_DIR)/libmlx.a
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

LIBFT_DIR		= lib/libft
LIBFT				= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

w = 1
ifeq '$(w)' '1'
CFLAGS += -Wextra -Werror -Wall
endif

debug = 1
ifeq '$(debug)' '1'
CFLAGS += -g
endif

asan = 0
ifeq '$(asan)' '1'
CFLAGS += -fsanitize=address
endif

all: $(MLX) $(LIBFT)
	@mkdir -p build/bin
	@$(MAKE) $(NAME)

$(NAME): $(CMD) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $(MLX_FLAGS) $(LIBFT_FLAGS) $(CMD) $(OBJS) -o $(NAME)

$(MLX):
	@curl -O https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz
	@tar -xvf minilibx_opengl.tgz
	@mkdir -p $(MLX_DIR)
	@mv minilibx_opengl_20191021/* $(MLX_DIR)
	@$(RM) minilibx_opengl_20191021
	@$(RM) minilibx_opengl.tgz
	make -s -C $(MLX_DIR)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBFT) & wait

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re