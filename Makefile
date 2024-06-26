# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2024/05/23 17:55:01 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = pipex_main.c pipex_comm_utils.c pipex_helpers.c

OFILES = $(CFILES:%.c=%.o)

OBJ = $(OFILES)

PATH_LFT = libft/libft.a

PATH_PTF = printf/libftprintf.a

CFLAGS = -Wall -Wextra -Werror

CC = cc

ARLIB = ar rc

RM = rm -f

NAME = pipex

%.o: %.c  pipex.h Makefile libft printf
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES) 
	make -C libft/
	make -C printf/
	$(CC) $(CFLAGS) $(OFILES) $(PATH_LFT) $(PATH_PTF) -o $(NAME)

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