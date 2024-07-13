# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:57:50 by madamou           #+#    #+#              #
#    Updated: 2024/07/13 06:06:48 by madamou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

C_FLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs/

PARSING = $(addprefix parsing/, parsing_args_bonus.c parsing_utils_bonus.c \
				init_struct_bonus.c)

PROCESS = $(addprefix process/, process_bonus.c routine_bonus.c process_utils_bonus.c \
				routine2_bonus.c semaphores_bonus.c checker.c)

UTILS = $(addprefix utils/, utils_bonus.c ft_itoa_bonus.c)

OBJS_DIR = .objets/

SRCS = main_bonus.c $(PARSING) $(PROCESS) $(UTILS)

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)


DIR_DUP = mkdir -p $(@D)

NAME = philo_bonus

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
