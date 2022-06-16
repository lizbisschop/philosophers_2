# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lbisscho <lbisscho@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/19 10:24:00 by lbisscho      #+#    #+#                  #
#    Updated: 2022/06/16 14:36:52 by lbisscho      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =  main.c init_philo.c init_table.c threading.c utils.c utils_2.c eat_sleep_think.c custom_print.c

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I include/philo.h

all: $(NAME)

ifdef DEBUG
FLAGS += -fsanitize=address -g
endif

ifdef THREAD 
FLAGS += -fsanitize=thread -g
endif

ifdef OG
Flags+= -O3
endif

$(NAME): $(OBJ)
	gcc $(FLAGS) -pthread $(INCLUDES) $^ -o $@
# $(OBJ):
# 	gcc $(FLAGS) -c $(SRCS) -O3
%.o: %.c
	$(CC) -c $(FLAGS) -o $@ $<
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all