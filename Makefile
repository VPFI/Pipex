# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2024/05/22 16:42:51 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = pipex_main.c pipex_utils.c

OFILES = $(CFILES:%.c=%.o)

OBJ = $(OFILES)

PATH_LFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

CC = cc

ARLIB = ar rc

RM = rm -f

NAME = pipex

%.o: %.c  Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES) 
	make -C libft/
	$(CC) $(CFLAGS) $(OFILES) $(PATH_LFT) -o $(NAME)

debug: $(OFILES) 
	make -C libft/
	$(CC) -g $(CFLAGS) $(OFILES) $(PATH_LFT) -o $(NAME)

sanitize: $(OFILES) 
	make -C libft/
	$(CC) -g -fsanitize=address $(CFLAGS) $(OFILES) $(PATH_LFT) -o $(NAME)

clean:
	make clean -C libft 
	$(RM) $(OBJ)

fclean:	clean
	make fclean -C libft
	$(RM) $(NAME)

re:	fclean all
	make re -C libft

.PHONY: all clean fclean re