# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 17:34:45 by vperez-f          #+#    #+#              #
#    Updated: 2024/05/23 17:25:52 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = ft_memmove.c ft_strjoin.c ft_strrchr.c ft_atoi.c ft_memset.c \
		 ft_strlcat.c ft_toupper.c ft_bzero.c ft_isalpha.c ft_strlcpy.c \
		 ft_substr.c ft_calloc.c ft_isdigit.c ft_strlen.c ft_memchr.c \
		 ft_isprint.c ft_tolower.c ft_memcmp.c	ft_strchr.c \
		 ft_strncmp.c ft_memcpy.c ft_strdup.c ft_strnstr.c ft_split.c \
		 ft_strtrim.c ft_isalnum.c ft_isascii.c ft_strmapi.c ft_striteri.c \
		 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		 ft_itoa.c

BCFILES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		  ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		  ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OFILES = $(CFILES:%.c=%.o)

BOFILES = $(BCFILES:%.c=%.o)

OBJ = $(OFILES) $(BOFILES) 

# DEP = $(OBJ:%.o=%.d) $(.bonus)

# DFLAGS = -MMD -MP

CFLAGS = -Wall -Wextra -Werror

CC = cc

ARLIB = ar rc

RM = rm -f

NAME = libft.a

%.o: %.c 	 libft.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	$(ARLIB) $(NAME) $(OFILES)
	
bonus: .bonus 
	
.bonus: $(OBJ)
	$(ARLIB) $(NAME) $(OBJ)
	@touch .bonus

clean:
	$(RM) $(OBJ) .bonus

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY = all clean fclean re
