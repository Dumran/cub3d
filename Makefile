CC					= clang
CFLAGS			=
PROGRAM			= cub3d
SRC_DIR			= src
CMD_DIR			= cmd
BUILD_DIR		= build
BIN_DIR			= $(BUILD_DIR)/bin
INC_DIR			= -Iinc -I$(MLX_DIR)
NAME				= $(BIN_DIR)/$(PROGRAM)
SRCS				=
OBJS				= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
CMD					= $(CMD_DIR)/$(PROGRAM).c
RM					= rm -rf

MLX_DIR			= lib/libmlx
MLX					= $(MLX_DIR)/libmlx.a
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

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

all: $(MLX)
	@mkdir -p build/bin
	@$(MAKE) $(NAME)

$(NAME): $(CMD) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $(MLX_FLAGS) $(CMD) $(OBJS) -o $(NAME)

$(MLX):
	@curl -O https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz
	@tar -xvf minilibx_opengl.tgz
	@mkdir -p $(MLX_DIR)
	@mv minilibx_opengl_20191021/* $(MLX_DIR)
	@$(RM) minilibx_opengl_20191021
	@$(RM) minilibx_opengl.tgz
	make -s -C $(MLX_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -s -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME) & wait

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re