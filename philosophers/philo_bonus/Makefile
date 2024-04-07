NAME := philo_bonus

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
#-fsanitize=thread -g3
INCLUDES := -I ./includes

SRCS_DIR := srcs
OBJS_DIR := objs

FILES := main \
        convert_input \
        init \
        philosopher \
        monitor_i \
        monitor_ii \
        time_utils \
        utils_i \
        utils_ii
SRCS := $(foreach src, $(FILES), $(SRCS_DIR)/$(src).c)
OBJS := $(foreach src, $(FILES), $(OBJS_DIR)/$(src).o)

#--------------------------------------------------------------------------#

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
