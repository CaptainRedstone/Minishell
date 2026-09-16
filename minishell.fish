function minishell

    set -l args $argv

    clear

    make -C /home/captainredstone/dev/Minishell re
    or return

    clear

    if contains -- -c  $args
        set args (string match -v -- '-c' $args)

        cd /home/captainredstone/dev/Minishell
    end

    if contains -- -v $args
        set args (string match -v -- '-v' $args)

        valgrind \
            -s \
            --track-fds=yes \
            --leak-check=full \
            --track-origins=yes \
            --show-leak-kinds=all \
            --suppressions=/home/captainredstone/dev/Minishell/supp.supp \
            /home/captainredstone/dev/Minishell/minishell $args
    else
        /home/captainredstone/dev/Minishell/minishell $args
    end
end