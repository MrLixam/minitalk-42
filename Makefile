# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 19:22:15 by lvincent          #+#    #+#              #
#    Updated: 2023/04/18 20:38:37 by lvincent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CC = clang

FLAGS = -Wall -Werror -Wextra -I ./libft

all: libft server client 

bonus: libft server_bonus client_bonus

libft:
	@make -C libft

server:
	@$(CC) -o server server.c ./libft/libft.a $(CFLAGS)

client:
	@$(CC) -o client client.c ./libft/libft.a $(CFLAGS)

server_bonus:
	@$(CC) -o server_bonus server_bonus.c ./libft/libft.a $(CFLAGS)

client_bonus:
	@$(CC) -o client_bonus client_bonus.c ./libft/libft.a $(CFLAGS)

clean:
	@make clean -C libft

fclean: clean
	rm -f client
	rm -f client_bonus
	rm -f server
	rm -f server_bonus
	rm -f libft/libft.a

re: fclean all

re_b: fclean bonus

.PHONY: all clean fclean re libft server client bonus client_bonus server_bonus
