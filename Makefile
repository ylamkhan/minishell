
SRCS = get_next_line.c\
			get_next_line_utils.c\
			main.c\
			expand_var.c\
			expand_var1.c\
			fill_nodes.c\
			heredoc.c\
			parsing.c\
			sign.c\
			split.c\
			trim_all.c\
			prompt.c\
			builtin.c\
			env.c\
			error.c\
			erro1.c\
			execute.c\
			execute1.c\
			execute2.c\
			functions.c\
			functions1.c\
			matrix.c\
			get_files.c\
			cmdsub.c\
			syntax_error.c\
			export.c\
			export1.c


			
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
NAME = minishell
O_SRCS = $(SRCS:%.c=%.o)

RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(O_SRCS)
	@stty -echoctl
	@make -sC libft/
	$(CC) $(CFLAGS)  $(SRCS) libft/libft.a -o  $(NAME) -lreadline -L/goinfre/zsaoud/homebrew/opt/readline/lib -I/goinfre/zsaoud/homebrew/opt/readline/include
clean:
	@make clean -sC libft/
	$(RM) $(O_SRCS)

fclean: clean
	@make fclean -sC libft/
	$(RM) $(NAME)

re: fclean all

run :
	make
	clear
	./minishell

.PHONY: all clean fclean re