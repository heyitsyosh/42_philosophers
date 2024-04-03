NAME = philo

FILES = main\
		convert_input\
		init\
		philosopher\
		monitor\
		time_utils\
		utils\
		atoi
SRCS_DIR = srcs/
OBJS_DIR = objs/
SRCS = $(foreach src,$(FILES),./srcs/$(src).c)
OBJS = $(foreach src,$(FILES),./objs/$(src).o)


CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -I ./includes
#-fsanitize=thread -g3

#--------------------------------------------------------------------------#

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS)

clean:
	$(RM) $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re