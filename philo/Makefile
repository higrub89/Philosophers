# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhiguita <rhiguita@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 16:04:17 by rhiguita          #+#    #+#              #
#    Updated: 2025/11/02 01:22:24 by rhiguita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME				= philo

INC						= -Iinc/
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -g -pthread -I$(INC)
RM					= rm -f

# Source Files
COMMANDS_DIR		=	main.c   \
						time.c   \
						utils.c  \
						init.c	  \
						parser.c \
						simulation.c \
						monitor.c \
						actions.c 
						

# Concatenate all source files
SRCS 				= $(COMMANDS_DIR) 

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:				
					@make -s all

all: 				$(NAME)

$(NAME): 			$(OBJ)
					@$(CC) $(CFLAGS) $(INC) $(OBJ)  -o $(NAME) 2>&1 

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@echo "compiling $<"
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 2>&1

clean:
					@$(RM) -r $(OBJ_DIR)
					@echo "Delete files objets"

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM)
					@echo "Delete all files"

re: 				fclean all
					@echo "Finsh Recompiling"

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re
