valgrind \
        --leak-check=full \
        --track-origins=yes \
        --show-leak-kinds=all \
        --suppressions=./ignore_readline_leaks.supp \
        --track-fds=yes \
        ./minishell