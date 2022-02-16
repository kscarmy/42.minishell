NAME_LIB = minishell.a

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

GNL_C = srcs/gnl/get_next_line.c\
			srcs/gnl/get_next_line_bis.c\
			srcs/gnl/get_next_line_utils.c\

INIT_C = srcs/init/ft_token.c\
			srcs/init/ft_env.c\

UTILS_C = srcs/utils/ft_write.c\
			srcs/utils/ft_str.c\


PARS_C = srcs/parsing/ft_cut_echo.c\
			srcs/parsing/ft_cut_input.c\

CMD_C = srcs/cmd/ft_echo.c\
			srcs/cmd/ft_read_token_list.c\

MAIN_C = srcs/main.c\

OBJS = get_next_line.o\
			get_next_line_bis.o\
			get_next_line_utils.o\
			ft_token.o\
			ft_env.o\
			ft_write.o\
			ft_cut_echo.o\
			ft_cut_input.o\
			ft_str.o\
			ft_echo.o\
			ft_read_token_list.o\



all : $(NAME)

$(NAME) :
	@$(CC) $(CFLAGS) $(GNL_C) $(INIT_C) $(UTILS_C) $(PARS_C) $(CMD_C) -c
	@ar -rc $(NAME_LIB) $(OBJS)
	@ranlib $(NAME_LIB)
	@$(CC) $(CFLAGS) $(MAIN_C) $(NAME_LIB) -o $(NAME)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_LIB)

re : fclean all
	@rm -rf $(OBJS)
