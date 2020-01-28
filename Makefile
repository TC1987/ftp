# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcho <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/17 23:47:20 by tcho              #+#    #+#              #
#    Updated: 2019/03/14 21:32:49 by tcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ftp
CLIENT = client_src/client \
		 client_src/client_files \
		 client_src/client_info \
		 client_src/client_local \
		 client_src/client_requests
SERVER = server_src/server \
		 server_src/server_commands \
		 server_src/server_files \
		 server_src/server_setup
COMMON = common
CLIENT_SRC = $(addsuffix .c, $(CLIENT))
SERVER_SRC = $(addsuffix .c, $(SERVER))
COMMON_SRC = $(addsuffix .c, $(COMMON))
CLIENT_EXE = client
SERVER_EXE = server
INCLUDES = -I . -I ./libft
LIB = -L ./libft -lft
CC = gcc -Wall -Wextra -Werror
SANITIZE = -fsanitize=address

all: $(CLIENT_EXE) $(SERVER_EXE)

$(CLIENT_EXE): $(CLIENT_SRC) $(COMMON_SRC)
	make -C ./libft
	$(CC) $(CLIENT_SRC) $(COMMON_SRC) $(INCLUDES) -I ./client $(LIB) -o $(CLIENT_EXE)

$(SERVER_EXE): $(SERVER_SRC) $(COMMON_SRC)
	$(CC) $(SERVER_SRC) $(COMMON_SRC) $(INCLUDES) -I ./server $(LIB) -o $(SERVER_EXE)

clean:
	make clean -C ./libft

fclean:
	/bin/rm -f $(CLIENT_EXE)
	/bin/rm -f $(SERVER_EXE)
	make fclean -C ./libft

re: fclean all
