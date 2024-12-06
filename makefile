# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 13:05:50 by lumiguel          #+#    #+#              #
#    Updated: 2024/12/06 13:05:51 by lumiguel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# Variables
NAME = philo
CC = cc

CFLAGS = -g -Wall -Wextra -Werror #-pthread -fsanitize=address \

SRC_DIR = src
OBJ_DIR = obj
SRC = $(SRC_DIR)/args.c $(SRC_DIR)/main.c $(SRC_DIR)/philos.c $(SRC_DIR)/utils.c \
      $(SRC_DIR)/death.c $(SRC_DIR)/routine.c $(SRC_DIR)/time.c
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
