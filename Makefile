CC = gcc

CFLAGS = -Wall -Werror -Wextra

CLIENT = client

SERVER = server

NAME = ignore

all: $(CLIENT) $(SERVER)

$(NAME): all 

$(CLIENT): client.c
	$(CC) $(CFLAGS) client.c -o client
$(SERVER): server.c
	$(CC) $(CFLAGS) server.c -o server

bonus: all

clean:
	rm -rf client server
fclean: clean

re: clean all

.PHONY: all clean fclean re