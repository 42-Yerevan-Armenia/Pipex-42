NAME		=	libft.a

SRCS		=	$(wildcard *.c)
				
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CC			=	cc

RM			=	rm -f

CFLAGS		=	-Wall -Werror -Wextra

AR			=	ar rcs

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
				$(AR) $(NAME) $(OBJS)

clean:		
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
	