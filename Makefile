SRCS = main.c ft_builtins.c ft_init.c ft_redirs.c get_next_line.c

OBJS		=	${SRCS:.c=.o}

NAME		=	minishell

HEADER	= 	minishell.h

MAKELIB		=	$(MAKE) -C ./libft

MAKELIBBONUS	=	$(MAKE) bonus -C ./libft

RM			=	rm -f

CC			=	gcc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -g -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
		$(MAKELIB)
		$(MAKELIBBONUS)
		mv -f ./libft/libft.a ./
		$(CC) $(OBJS) libft.a -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}
			$(MAKE) clean -C ./libft

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re