# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 22:20:51 by marvin            #+#    #+#              #
#    Updated: 2023/09/06 22:20:51 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS += fsanitize=thread

#LIB = -lpthread

SRC     =  philo_utils.c \
			InitData.c \
			philo.c \
			routine.c \

OBJ = $(SRC:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) $< -o $@

$(NAME): $(LIBFT) $(SRC)
		$(CC) $(SRC) $(CFLAGS) $(LIB) -o $(NAME)

all: $(NAME)

clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re