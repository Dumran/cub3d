CC          = gcc
CFLAGS      =
PROGRAM     = cub3d
SRC_DIR     = src
CMD_DIR     = cmd
BUILD_DIR   = build
BIN_DIR     = $(BUILD_DIR)/bin
INC_DIR     = -Iinc -I$(MLX_DIR) -I$(LIBFT_DIR)
NAME        = $(BIN_DIR)/$(PROGRAM)
SRCS        =   src/dispose.c \
                src/err.c \
                src/file.c \
                src/game.c \
                src/hook.c \
                src/init.c \
                src/key_util.c \
                src/key.c \
                src/map_data_util.c \
                src/map_data.c \
                src/map_meta_util.c \
                src/map_meta.c \
                src/render.c \
                src/texture.c \
                src/util_str.c \
                src/util.c

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
CMD         = $(CMD_DIR)/$(PROGRAM).c
RM          = rm -rf

MLX_DIR     = lib/libmlx
MLX         = $(MLX_DIR)/libmlx.a

LIBFT_DIR   = lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# OS Tespiti
UNAME_S := $(shell uname -s)

# MacOS ve Linux için farklı MLX_FLAGS
ifeq ($(UNAME_S),Linux)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif

ifeq ($(UNAME_S),Darwin)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

w = 1
ifeq ('$(w)', '1')
CFLAGS += -Wextra -Werror -Wall
endif

debug = 1
ifeq ('$(debug)', '1')
CFLAGS += -g
endif

asan = 0
ifeq ('$(asan)', '1')
CFLAGS += -fsanitize=address
endif

all: $(MLX) $(LIBFT)
	@mkdir -p $(BIN_DIR)
	@$(MAKE) $(NAME)

$(NAME): $(CMD) $(OBJS) inc/cub3d.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $(MLX_FLAGS) $(LIBFT_FLAGS) $(CMD) $(OBJS) -o $(NAME)

$(MLX):
	@curl -O https://cdn.intra.42.fr/document/document/28880/minilibx-linux.tgz
	@tar -xvf minilibx-linux.tgz
	@mkdir -p $(MLX_DIR)
	@mv minilibx-linux/* $(MLX_DIR)
	@$(RM) minilibx-linux
	@$(RM) minilibx-linux.tgz
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
