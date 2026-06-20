NAME        = minishell

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft

# Source files
SRCS        = $(SRC_DIR)/main.c \
				$(SRC_DIR)/cd.c \
				$(SRC_DIR)/pwd.c \
				$(SRC_DIR)/env.c \
				$(SRC_DIR)/free.c \
				$(SRC_DIR)/echo.c \
				$(SRC_DIR)/exit.c \
				$(SRC_DIR)/color.c \
				$(SRC_DIR)/debug.c \
				$(SRC_DIR)/parse.c \
				$(SRC_DIR)/prompt.c \
				$(SRC_DIR)/signal.c \
				$(SRC_DIR)/errors.c \
				$(SRC_DIR)/welcome.c \
				$(SRC_DIR)/execute.c \
				$(SRC_DIR)/executable.c \
				$(SRC_DIR)/parse_utils.c \
				$(SRC_DIR)/tokenize.c \

# Object files
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3

FLAGS		= -lreadline

# ------------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(FLAGS) $(LIBFT) -o $(NAME)
	@echo "✅ minishell compiled successfully"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build libraries

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# ------------------------------------------------------------------------------

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: