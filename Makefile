RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
RESET	= \033[0;37m
BLUE	= \033[0;36m
SKY		= \033[1;36m

NAME		=	pipex

SRCS		=	main.c utils.c cmd.c
				
OBJS		=	$(SRCS:.c=.o)

CC			=	cc

RM			=	rm -f

CFLAGS		=	-Wall -Werror -Wextra -Iincludes

all:		$(NAME)

%.o: %.c $(NAME).h
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

$(NAME):	$(OBJS)
	@echo "$(BLUE)💡created ➡️  $(YELLOW)libft.a$(RESET)"
	@$(MAKE) -sC ./libft
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) sucessfully created$(RESET)"


clean:
	@echo "$(RED)♨️  clean  🗑$(RESET)"
	@$(MAKE) clean -sC ./libft
	@$(RM) $(OBJS)

fclean:		clean
	@echo "$(RED)♨️  fclean 🗑$(RESET)"
	@$(MAKE) fclean -sC ./libft
	@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
