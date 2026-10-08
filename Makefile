NAME        = minishell

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft

BUILTIN_DIR = $(SRC_DIR)/builtin
ENV_DIR     = $(SRC_DIR)/env
EXEC_DIR    = $(SRC_DIR)/exec
EXPAN_DIR   = $(SRC_DIR)/expansion
HD_DIR      = $(SRC_DIR)/heredocs
MAIN_DIR    = $(SRC_DIR)/main
PARSING_DIR = $(SRC_DIR)/parsing
TOKEN_DIR   = $(SRC_DIR)/tokenizing

# Source files
BUILTIN_SRCS =	$(BUILTIN_DIR)/cd.c \
				$(BUILTIN_DIR)/echo.c \
				$(BUILTIN_DIR)/exit.c \
				$(BUILTIN_DIR)/export.c \
				$(BUILTIN_DIR)/export_print.c \
				$(BUILTIN_DIR)/pwd.c \
				$(BUILTIN_DIR)/unset.c

ENV_SRCS =		$(ENV_DIR)/env.c \
				$(ENV_DIR)/env_init.c \
				$(ENV_DIR)/env_name.c \
				$(ENV_DIR)/env_utils.c

EXEC_SRCS =		$(EXEC_DIR)/exec.c \
				$(EXEC_DIR)/exec_builtin.c \
				$(EXEC_DIR)/exec_cmd.c \
				$(EXEC_DIR)/exec_path.c \
				$(EXEC_DIR)/exec_pipe.c \
				$(EXEC_DIR)/exec_redir.c \
				$(EXEC_DIR)/exec_wait.c

EXPAN_SRCS =	$(EXPAN_DIR)/expand.c \
				$(EXPAN_DIR)/expand_cmd.c \
				$(EXPAN_DIR)/expand_utils.c \
				$(EXPAN_DIR)/expand_var.c

HD_SRCS =		$(HD_DIR)/heredoc.c \
				$(HD_DIR)/heredoc_tmp.c \
				$(HD_DIR)/heredoc_utils.c

MAIN_SRCS =		$(MAIN_DIR)/errors.c \
				$(MAIN_DIR)/free.c \
				$(MAIN_DIR)/ft_sublst.c \
				$(MAIN_DIR)/input.c \
				$(MAIN_DIR)/main.c \
				$(MAIN_DIR)/prompt.c \
				$(MAIN_DIR)/signal.c \
				$(MAIN_DIR)/welcome.c

PARSING_SRCS =	$(PARSING_DIR)/parse.c \
				$(PARSING_DIR)/parse_argv.c \
				$(PARSING_DIR)/parse_check.c \
				$(PARSING_DIR)/parse_init_redir.c \
				$(PARSING_DIR)/parse_redir_utils.c \
				$(PARSING_DIR)/parse_utils.c

TOKEN_SRCS =	$(TOKEN_DIR)/token.c \
				$(TOKEN_DIR)/tokenize.c

SRCS =			$(BUILTIN_SRCS) \
				$(ENV_SRCS) \
				$(EXEC_SRCS) \
				$(EXPAN_SRCS) \
				$(HD_SRCS) \
				$(MAIN_SRCS) \
				$(PARSING_SRCS) \
				$(TOKEN_SRCS)

# Object files (the obj/ tree mirrors the src/ tree)
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

FLAGS       = -lreadline

# ------------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(FLAGS) $(LIBFT) -o $(NAME)
	@echo "✅ minishell compiled successfully"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c minishell.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libraries

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

# ------------------------------------------------------------------------------

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re