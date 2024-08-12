CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
LMLX = -Lminilibx-linux -lmlx -lXext -lX11 -lm

# Имя исполняемого файла
NAME = cub3D

# Библиотека libft
LIBFT = libft/libft.a

# Директории исходных файлов
SRC_DIR = src
GNL_DIR = get_next_line
LIBFT_DIR = libft

BGreen=\033[1;32m
BRed=\033[1;31m
BFiol=\033[0;35m

# Исходные файлы
SRC_GNL = get_next_line.c get_next_line_utils.c
SRC = main.c map.c errors.c game_mlx.c map_checking.c \
color.c game_init.c utils.c end.c

# Все исходные файлы
ALL_SRC = $(addprefix $(SRC_DIR)/, $(SRC)) $(addprefix $(GNL_DIR)/, $(SRC_GNL))

# Все объектные файлы
OBJ = $(ALL_SRC:.c=.o)

# Основная цель
all: tag $(NAME)

# Сборка исполняемого файла
$(NAME): $(LIBFT) $(OBJ) tag
	@echo
	@echo
	@echo "\n               $(BGreen)Building target file: $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LMLX) -o $@ > /dev/null
	@echo "$(BGreen)                   🕹  LET'S BEGIN!!! 🎮"
	@echo
	@echo

# Компиляция исходных файлов в объектные
%.o: %.c
	@$(CC) $(CFLAGS) -Iminilibx-linux -Ilibft -c $< -o $@ > /dev/null

# Сборка библиотеки libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

# Очистка
clean:
	@echo "$(BRed)Cleaning......"
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(RM) $(OBJ) .tag
	@echo "              ............ READY"

# Полная очистка
fclean: clean
	@echo
	@echo
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(NAME)

# Пересборка
re: fclean all

.PHONY: all clean fclean re

tag:
	@if [ ! -e .tag ]; then \
		echo "$(BFiol)"; \
		echo "	██████╗ ██╗   ██╗██████╗ $(BGreen)██████╗ ██████╗"; \
		echo " $(BFiol)	██╔════╝██║   ██║██╔══██╗$(BGreen)╚════██╗██╔══██╗"; \
		echo "	$(BFiol)██║     ██║   ██║██████╔╝$(BGreen) █████╔╝██║  ██║"; \
		echo "	$(BFiol)██║     ██║   ██║██╔══██╗ $(BGreen)╚═══██╗██║  ██║"; \
		echo "	$(BFiol)╚██████╗╚██████╔╝██████╔╝$(BGreen)██████╔╝██████╔╝"; \
		echo "	$(BFiol) ╚═════╝ ╚═════╝ ╚═════╝ $(BGreen)╚═════╝ ╚═════╝ "; \
  		touch .tag; \
	fi        
