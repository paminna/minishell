SRCS = ft_echo.c 

OBJS		=	${SRCS:.c=.o}

NAME		=	mini

HEADER	= 	minishell.h

MAKELIB		=	$(MAKE) -C ./libft

RM			=	rm -f

CC			=	gcc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -g -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
		$(MAKELIB)
		mv -f ./libft/libft.a ./
		$(CC) $(OBJS) -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}
			$(MAKE) clean -C ./libft

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re