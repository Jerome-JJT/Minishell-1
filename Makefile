CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address
LIBFT			= -L./libft -lft
INCLUDES		= -I libft/include/ -I ./ -I $(HOME)/.brew/Cellar/readline/8.2.1/include
BUILTINS_PATH	= ./src/builtins
EXEC_PATH		= ./src/execution
LIST_PATH		= ./src/list
SRC_PATH		= ./src
UTILS_PATH		= ./src/utils
PARSE_PATH		= ./src/parsing
SIGNALS_PATH	= ./src/signals

NAME			=	minishell

SRC				=	main.c

UTILS			=	utils.c \
					test.c \
					utils_3.c \
					utils_2.c \
					utils_4.c \
					utils_5.c \
					error.c

SIGNALS			=	handle_signals.c

PARSE			=	red.c \
					word.c \
					pipe.c \
					space.c \
					quote.c \
					syntax.c \
					parse_shell.c \
					parse_to_exec.c

EXEC			=	execution.c \
					init_exec.c \
					utils_exec.c \
					handle_cmd.c \
					handle_process.c \
					handle_redirections.c \
					error_exec.c \
					child_process.c \
					split_exec.c \
					handle_builtins.c \
					handle_heredoc.c \
					handle_append.c \
					utils_heredoc.c \
					ft_heredoc.c

BUILTINS		=	echo.c \
					env.c \
					exit.c \
					pwd.c \
					cd.c \
					export.c \
					unset.c

LIST			=	list_utils.c \
					list_tok.c \
					list_utils2.c

_BLUE			=	\e[34m
_PURPLE			=	\e[35m
_CYAN			=	\e[36m
_END			=	\e[0m


SRCS 			=	$(addprefix $(SRC_PATH)/,$(SRC)) $(addprefix $(BUILTINS_PATH)/,$(BUILTINS)) $(addprefix $(LIST_PATH)/,$(LIST)) $(addprefix $(UTILS_PATH)/,$(UTILS)) $(addprefix $(PARSE_PATH)/,$(PARSE)) $(addprefix $(EXEC_PATH)/,$(EXEC)) $(addprefix $(SIGNALS_PATH)/,$(SIGNALS))
OBJS			=	$(SRCS:.c=.o)

%.o: %.c minishell.h
			@printf "minishell object :		$(_BLUE)%-33.33s\r$(_END)\n" $@
			@${CC} ${CFLAGS} $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS) libft/libft.a
			@printf "libft				[$(_BLUE)✓$(_END)]\n"
			@printf "minishell objects		[$(_BLUE)✓$(_END)]\n"
			@gcc $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) -l readline -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -o $(NAME)
			@printf "minishell			[$(_BLUE)✓$(_END)]\n"
			@printf "\n"
			@printf "Minishell --------------------------------------> Ready to use\n"

libft/libft.a :
			@$(MAKE) -C ./libft

all : 		$(NAME)

re:			fclean
			$(MAKE) $(NAME)

clean :
			@rm -rf $(OBJS)
			@$(MAKE) clean -C ./libft
			@printf "$(_PURPLE)MINISHELL object	deleted$(_END)\n"

fclean :	clean
			@$(MAKE) fclean -C ./libft
			@rm -rf $(NAME)
			@printf "$(_PURPLE)minishell		deleted$(_END)\n"

leaks :		all
			leaks --atExit -- ./$(NAME)
PHONY : re all clean fclean

title :
			@echo " "
			@echo " "
			@echo "	 _    _ _       _     _          _ _"
			@echo "	|  \/  (_)_ __ (_)___| |__   ___| | |"
			@echo "	| |\/| | | '_ \| / __| '_ \ / _ \ | |"
			@echo "	| |  | | | | | | \__ \ | | |  __/ | |"
			@echo "	|_|  |_|_|_| |_|_|___/_| |_|\___|_|_|"
			@echo ""
			@echo ""
			@echo ""
			@echo "				 _"
			@echo "				| |__  _   _ "
			@echo "				| '_ \| | | |"
			@echo "				| |_) | |_| |"
			@echo "				|_.__/ \__, |"
			@echo "				       |___/"
			@echo ""
			@echo ""
			@echo ""
			@echo "					 _   _ _      _    _ "
			@echo "					| \ | (_) ___| | _(_)"
			@echo "					|  \| | |/ __| |/ / |"
			@echo "					| |\  | | (__|   <| |"
			@echo "					|_| \_|_|\___|_|\_\_|"
			@echo ""
			@echo ""
			@echo ""


			@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡿⣿⣿⣿⣿⣽⣯⣿⣭⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
			@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡿⣿⣿⣿⣿⣽⣯⣿⣭⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
			@echo "				  ⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠋⠛⢶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡆⠀⠀⠉⠻⠷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠋⢡⣀⠈⠙⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠠⢤⣀⠀⠀⠈⢳⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠟⠈⠀⡁⢻⡓⠘⢿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡇⠀⠾⠄⠀⠀⠀⣿⣿⣟⡲⣤⡀⠀⠀⠀⠀⣰⣯⣤⠎⠰⡇⠀⣳⠀⠀⢻⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠀⠰⠦⣤⣀⠀⠈⠏⢿⡑⣌⡟⣦⡀⠀⣴⡟⠾⠓⠒⠒⠦⡀⢹⣇⠀⠘⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡆⣸⣾⣿⣿⣦⣄⡀⠈⣿⡈⣻⡏⢽⣾⢻⠁⢀⠀⠀⢀⣠⣝⣭⣿⠀⠀⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡍⠉⠵⢾⡗⠉⢧⢀⠻⣷⣿⣇⡾⠃⠘⠀⣄⠐⠀⠶⢟⣿⣿⣿⠀⠀⣿⣿⡱⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡻⣦⡀⠸⢯⠃⠈⠟⠀⠇⠀⠻⠃⠀⠀⢸⡿⠛⢰⣾⣿⣿⣿⠋⠀⣸⣿⡿⢽⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣟⡙⢶⡮⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⠁⢀⣾⢹⣿⠋⠛⠀⢠⣥⣿⡄⠘⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠌⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠼⠉⠈⠀⠀⠀⠀⢸⣅⣿⠿⠂⢸⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⡆⠀⣀⣀⣀⣼⡿⠻⠀⠁⠀⢿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠃⠀⠀⠀⠀⠀⠀⠀⢀⣠⠀⠀⠀⠀⠀⠀⠀⠀⠉⠣⣿⣍⣭⣉⠀⠀⠭⠖⢦⣼⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢷⡆⠀⠀⠀⠀⠀⣸⣿⡶⡶⢤⣄⣀⣸⢧⠀⠀⠀⠑⣦⣀⢪⡑⠦⡀⠀⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠾⡟⠀⠀⠀⠀⣠⣿⡿⠿⠷⠚⠉⠁⢉⠻⢽⣟⣀⠀⠀⠙⣦⡙⣷⡈⠣⡀⠸⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣾⠃⠀⠀⢠⣴⣿⡉⠉⠀⠀⠀⠀⠐⠛⠓⠀⠘⠛⠿⣶⡄⢹⣷⡜⣧⠀⠈⠀⢻⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⠃⠀⠀⠀⢹⡆⢿⡆⠀⠀⠀⠀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠙⢦⠻⡹⡌⢧⡀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠏⠀⠀⠀⠀⠀⣸⣷⣻⣷⣄⣤⠴⠒⠀⠠⠴⠤⠆⠀⠀⢦⣀⠀⠀⢳⡿⢿⡏⠳⣶⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣁⣀⠀⠀⣀⣀⣼⣯⣽⣿⠙⠿⠛⣠⣴⡄⠀⠀⠀⠐⠀⠀⢠⢹⠀⠀⠀⠓⢸⢧⠀⢹⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢺⣧⣽⣿⣿⠞⠋⠙⠛⠋⠿⢁⣠⣴⣋⣡⡤⠤⠤⠤⠤⠤⠤⣀⡈⢳⡇⠀⠀⠀⠸⣿⠀⣼⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣉⠀⠀⢀⣀⣤⣶⠿⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠳⢤⡀⠀⠀⢹⣰⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠛⠻⠟⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⢧⣾⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡿⣿⣿⣿⣿⣽⣯⣿⣭⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
			@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣿⣿⣷⣿⣿⣿⣿⣿⣽⣿⣿⣿⣿⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
