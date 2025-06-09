# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhiguita <rhiguita@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 16:04:17 by rhiguita          #+#    #+#              #
#    Updated: 2025/06/09 19:46:59 by rhiguita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME				= philosophers

INC						= -Iinc/
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -g -pthread -I$(INC)
RM					= rm -f

# Source Files
COMMANDS_DIR		=	srcs/philo.c 

# Concatenate all source files
SRCS 				= $(COMMANDS_DIR) 

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:				
					@make -s all

all: 				$(NAME)

$(NAME): 			$(OBJ)
					@$(CC) $(CFLAGS) $(INC) $(OBJ)  -o $(NAME) 2>&1 | lolcat

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@echo "compiling $<" | lolcat
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 2>&1 | lolcat

clean:
					@$(RM) -r $(OBJ_DIR)
					@echo "Delete files objets" | lolcat

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM)
					@echo "Delete all files" | lolcat

re: 				fclean all
					@echo "Delete all files and compiling now" | lolcat

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re
