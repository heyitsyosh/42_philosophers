NAME = philo

FILES = main\
		convert_input\
		init\
		philosopher\
		monitor\
		time_utils\
		utils
SRCS = $(foreach src,$(FILES),./srcs/$(src).c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread -I ./includes -fsanitize=thread -g3
#-fsanitize=thread -g3

#--------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re