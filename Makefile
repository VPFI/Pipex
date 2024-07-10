# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2024/07/09 18:44:12 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = pipex_main.c pipex_comm_utils.c pipex_helpers.c

OFILES = $(CFILES:%.c=%.o)

OBJ = $(OFILES)

PATH_LFT = libft/libft.a

PATH_PTF = printf/libftprintf.a

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak

CC = cc

ARLIB = ar rc

RM = rm -f

NAME = pipex

all: extra_make $(NAME)

extra_make:
	@printf "LIBFT: COMPILING...\n$(END)"
	@$(MAKE) -C libft/ --no-print-directory
	@printf "PRINTF: COMPILING...\n$(END)"
	@$(MAKE) -C printf/ --no-print-directory

$(NAME): $(OFILES) 
	$(CC) $(CFLAGS) $(OFILES) $(PATH_LFT) $(PATH_PTF) -o $(NAME)

%.o: %.c  pipex.h Makefile libft printf
	$(CC) $(CFLAGS) -c $< -o $@

debug: $(OFILES) 
	make -C libft/
	make -C printf/
	$(CC) -g $(CFLAGS) $(OFILES) $(PATH_LFT) $(PATH_PTF) -o $(NAME)

sanitize: $(OFILES) 
	make -C libft/
	make -C printf/
	$(CC) -g -fsanitize=address $(CFLAGS) $(OFILES) $(PATH_LFT) $(PATH_PTF) -o $(NAME)

clean:
	make clean -C libft/
	make clean -C printf/
	$(RM) $(OBJ)

fclean:	clean
	make fclean -C libft/
	make fclean -C printf/
	$(RM) $(NAME)

re:	fclean all
	make re -C libft/
	make re -C printf/

.PHONY: all clean fclean re