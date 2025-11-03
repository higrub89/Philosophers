# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 16:04:17 by rhiguita          #+#    #+#              #
#    Updated: 2025/11/02 15:46:03 by rhiguita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME				= philo

INC_DIR				= ./
SRC_DIR				= ./
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -g -pthread -I$(INC_DIR)
RM					= rm -f

# Source Files
SRCS_FILES		=	main.c   \
						time.c   \
						utils.c  \
						init.c	  \
						parser.c \
						simulation.c \
						monitor.c \
						actions.c 
						

# add prefix in all file.c
SRCS 				= $(addprefix $(SRC_DIR), $(SRCS_FILES)) 

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# --- TARGETS ---
all: 				$(NAME)

$(NAME): 			$(OBJ)
					@echo "exalting philo..."
					@$(CC) $(CFLAGS) $(INC) $(OBJ)  -o $(NAME) 2>&1 

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@mkdir -p $(OBJ_DIR)
					@echo "compiling ...$<"
					@$(CC) $(CFLAGS) -c $< -o $@ 2>&1

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
.PHONY: 			all clean fclean re
