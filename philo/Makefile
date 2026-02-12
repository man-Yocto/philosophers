NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
TARGET = $(NAME)
SRC = init.c main.c simu.c monitor_utils.c utils.c utils1.c utils2.c simu1.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re