CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

# Пути к библиотекам
LIBFT_DIR = libs/libft
MLX_DIR = libs/minilibx-linux

# Линковка с библиотеками
LMLX = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT = $(LIBFT_DIR)/libft.a

# Имя исполняемого файла
NAME = cub3D

# Директории исходных файлов и объектных файлов
SRC_DIR = src
GNL_DIR = get_next_line
BUILD_DIR = build

# Файлы в папке build
TAG_FILE = $(BUILD_DIR)/.tag
LOG_FILE = $(BUILD_DIR)/build.log

# Цвета для вывода текста
BGreen = \033[1;32m
BRed = \033[1;31m
BFiol = \033[0;35m

# Автоматический поиск всех .c файлов
SRC_FILES = $(shell find $(SRC_DIR) $(GNL_DIR) -name '*.c')
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_FILES := $(OBJ_FILES:$(GNL_DIR)/%.c=$(BUILD_DIR)/%.o)

# Основная цель
all: tag $(NAME)

# Сборка исполняемого файла
$(NAME): $(LIBFT) $(MLX_DIR)/libmlx.a $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	@printf "\n               $(BGreen)Building target file: $(NAME)\n"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(LMLX) -o $@ 2>> $(LOG_FILE) 
	@printf "$(BGreen)                   🎮  LET'S BEGIN!!! 🎮\n\n\n"

# Компиляция исходных файлов в объектные
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@ 2>> $(LOG_FILE)

$(BUILD_DIR)/%.o: $(GNL_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@ 2>> $(LOG_FILE)

# Создание директории для объектных файлов
$(BUILD_DIR):
	@mkdir -p $@

# Сборка библиотеки libft
$(LIBFT):
	@mkdir -p $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) -s > /dev/null 2>> $(LOG_FILE)

# Сборка библиотеки MiniLibX
$(MLX_DIR)/libmlx.a:
	@mkdir -p $(BUILD_DIR)
	@$(MAKE) -C $(MLX_DIR) -s > /dev/null 2>> $(LOG_FILE)

# Очистка объектных файлов и временных файлов
clean:
	@echo "$(BRed)🤖🧹 Initiating cleanup protocol..."
	@mkdir -p $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean -s > /dev/null 2>> $(LOG_FILE)
	@$(MAKE) -C $(MLX_DIR) clean -s > /dev/null 2>> $(LOG_FILE)
	@$(RM) -r $(BUILD_DIR)
	@echo "$(BGreen)All systems clear, commander! ✨"

# Полная очистка (включая исполняемый файл)
fclean: clean
	@mkdir -p $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean -s > /dev/null 2>> $(LOG_FILE)
	@$(RM) $(NAME)
	@echo "$(BGreen)👾 Nothing to see here, just a spotless void...🕳️  Move along!"
	@$(RM) -r $(BUILD_DIR)

# Пересборка всего проекта
re: fclean all

.PHONY: all clean fclean re

# Дополнительная цель tag для красивого вывода 
tag:
	@if [ ! -e $(TAG_FILE) ]; then \
		mkdir -p $(BUILD_DIR); \
		echo "$(BFiol)\n\n\n"; \
		echo "	██████╗ ██╗   ██╗██████╗ $(BGreen)██████╗ ██████╗"; \
		echo " $(BFiol)	██╔════╝██║   ██║██╔══██╗$(BGreen)╚════██╗██╔══██╗"; \
		echo "	$(BFiol)██║     ██║   ██║██████╔╝$(BGreen) █████╔╝██║  ██║"; \
		echo "	$(BFiol)██║     ██║   ██║██╔══██╗ $(BGreen)╚═══██╗██║  ██║"; \
		echo "	$(BFiol)╚██████╗╚██████╔╝██████╔╝$(BGreen)██████╔╝██████╔╝"; \
		echo "	$(BFiol) ╚═════╝ ╚═════╝ ╚═════╝ $(BGreen)╚═════╝ ╚═════╝ "; \
		echo "$(BFiol)\n"; \
  		touch $(TAG_FILE); \
	fi
