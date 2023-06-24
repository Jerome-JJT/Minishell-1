CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
SRC_PATH	= ./src/function
SORT_PATH	=./src/tri/
LIST_PATH	= ./src/list/simpl_list/
DLIST_PATH	= ./src/list/doubl_list/
CLIST_PATH	=./src/list/circular_list/

SRC	= ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_atoi.c \
			ft_strncmp.c \
			ft_memcmp.c \
			ft_itoa.c \
			ft_strdup.c \
			ft_strchr.c \
			ft_nbrlen_d.c \
			ft_nbrlen_exa.c \
			ft_strrchr.c \
			ft_strlen.c \
			ft_islower.c \
			ft_isupper.c \
			ft_free_2da.c \
			ft_free_arrays.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_split.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strmapi.c \
			ft_substr.c \
			ft_strnstr.c \
			ft_bzero.c \
			ft_nbrlen_b.c \
			ft_itob.c \
			ft_btoi.c \
			ft_atob.c \
			ft_power.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_putendl_fd.c \
			ft_calloc.c \
			ft_memset.c \
			ft_memchr.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_striteri.c \
			ft_free.c \
			ft_swap.c \
			ft_exit.c \
			ft_strcmp.c \
			my_malloc.c

SORT_SRC		= bubblesort.c \
				quicksort.c

SRC_SLIST	= ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c

SRC_DLIST	= ft_dlst_addback.c \
				ft_dlst_addfront.c \
				ft_dlst_clear.c \
				ft_dlst_new.c \
				ft_dlst_newcontent.c \
				ft_pop_front.c \
				ft_pop_back.c \
				ft_dlst_add.c \
				ft_dlst_delone.c


### COLORS ###
_BOLD        = \e[1m
_UNDERLINE   = \e[4m
_BLACK       = \e[30m
_RED         = \e[31m
_GREEN       = \e[32m
_YELLOW      = \e[33m
_BLUE        = \e[34m
_VIOLET      = \e[35m
_CYAN        = \e[36m
_END         = \e[0m

SRCS	= $(addprefix $(SRC_PATH)/,$(SRC)) $(addprefix $(LIST_PATH)/,$(SRC_SLIST)) $(addprefix $(DLIST_PATH)/,$(SRC_DLIST)) $(addprefix $(SORT_PATH)/,$(SORT_SRC))
OBJS	= $(SRCS:.c=.o)

%.o: %.c
			@printf "Libft object :			$(_BLUE)%-33.33s\r$(_END)\n" $@
			@${CC} ${CFLAGS} -c $< -o $@


NAME	= libft.a

RM		= rm -f

all :	$(NAME)

$(NAME) : $(OBJS)
		@ar -rs $(NAME) $(OBJS)
		@$(RM) $(OBJS)

re : fclean $(NAME)

clean :
		$(RM) *.o $(SRC_PATH)*.o $(GNL_SRC_FOLDER)*.o $(PRINTF_SRC_FOLDER)*.o

fclean : clean
		@$(RM) $(NAME)

.PHONY: all re clean fclean