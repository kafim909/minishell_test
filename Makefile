NAME		=	minishell

PARS		=	main.c \
				srcs/parsing/parser.c \
				srcs/parsing/ft_strtok.c \
				srcs/parsing/ft_strtok_utils.c \
				srcs/parsing/utils.c \
				srcs/parsing/parser_utils.c \
				srcs/parsing/check_env_var.c \

EXE			=	srcs/exec/builtins.c\
				srcs/exec/exec.c\
				srcs/exec/pipes.c\
				srcs/exec/utils.c\
				
LIBFT		= ./libft/

NAMELFT		= ./libft/libft.a

OBJS		=	$(PARS:c=o) $(EXE:c=o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g3 \

INC			= 	-I./inc/


all:			$(OBJS) $(NAME)

%.o:		%.c
				@echo "Compiling $<"
				@$(CC) $(CFLAGS) -c $(INC) $< -o $(<:c=o)
				@echo "Compiling OK!"

$(NAME):	$(OBJS)
				@make all -s -C ./libft
				@echo "Linking $^"
				@cc $(CFLAGS) ${NAMELFT} -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/include/readline/ -ltermcap $^ -o $@ 
				@echo "Executable created!"
clean:
				@echo "Cleaning objects..."
				@rm -f $(OBJS) $(BONUS_OBJS)
				@echo "Cleaned up!"

fclean:		clean
				@make fclean -s -C ./libft
				@echo "Removing executable..."
				@rm -f $(NAME)
				@echo "Removed!"

re:			fclean all

.PHONY:		all clean fclean re
