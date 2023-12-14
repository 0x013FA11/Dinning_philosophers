NAME = philo
SRCS = death.c \
		main.c \
		routine.c \
		utils.c \
		utils2.c 
OBJS = $(patsubst %.c, %.o, $(SRCS))
CC = cc
CFLAGS = -pthread -Wall -Wextra -Werror  -g #-fsanitize=address,undefined
all: $(NAME) 

%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@
clean:
	rm -f $(OBJS) $(BOBJS)
fclean: clean
	rm -f $(NAME) $(BNAME)
re: fclean all 