NAME = philo_bonus

FILES = main\
		convert_input\
		init\
		philosopher\
		monitor\
		monitor_utils\
		time_utils\
		utils
SRCS = $(foreach src,$(FILES),./srcs/$(src).c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread
#-fsanitize=thread -g3

#--------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re