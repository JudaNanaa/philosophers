# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:57:50 by madamou           #+#    #+#              #
#    Updated: 2024/07/04 22:47:39 by madamou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

C_FLAGS = -Wall -Wextra -Werror -O3 -g3

SRCS_DIR = srcs/

PARSING = $(addprefix parsing/, parsing_args.c parsing_utils.c init_struct.c)

THREAD = $(addprefix thread/, threads.c threads_utils.c routine.c routine2.c)

UTILS = $(addprefix utils/, utils.c)

OBJS_DIR = .objets/

SRCS = main.c $(PARSING) $(THREAD) $(UTILS)

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DIR_DUP = mkdir -p $(@D)

NAME = philo 

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(C_FLAGS) $^ -pthread -std=c11 -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(DIR_DUP)
	$(CC) $(C_FLAGS) -c  -pthread -std=c11 $< -o $@


bonus :  $(BONUS)

clean : 
	rm -rf $(OBJS_DIR) 

fclean : clean
	rm -rf $(NAME) 

re : fclean all

.PHONY : all clean fclean re 
