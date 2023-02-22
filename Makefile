# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 19:22:15 by lvincent          #+#    #+#              #
#    Updated: 2023/02/22 20:03:11 by lvincent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wall -Werror -Wextra -I ./libft

all : libft server client

libft :
	@make -C libft

server:
	@$(CC) -o server server.c ./libft/libft.a $(CFLAGS)

client:
	@$(CC) -o client client.c ./libft/libft.a $(CFLAGS)
	
clean:
	@echo ""

fclean: clean
	rm client
	rm server

re: fclean all

.PHONY: all clean fclean re execs