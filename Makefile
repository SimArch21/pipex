# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 11:28:35 by simarcha          #+#    #+#              #
#    Updated: 2024/04/21 12:11:08 by simarcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror
NAME			= pipex
RM				= rm -rf

#FILES AND PATHS
#HEADER
INCLUDE_DIR		= inc/
INCLUDE_FILES	= pipex.h \
				  get_next_line.h
INCLUDE			= $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))

#SRCS - Where the main files for this project are located
SRCS_DIR		= srcs/
SRCS_FILES		= pipex.c \
				manage_command.c \
				create_command.c \
				manage_heredoc.c
SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJ_SRCS		= $(SRCS:.c=.o)

#UTILS - The annexes functions that I used for this project
UTILS_DIR		= utils/
UTILS_FILES		= get_next_line.c \
				  ft_split.c \
				  ft_split_for_slash.c \
				  libft_functions.c 
UTILS			= $(addprefix $(UTILS_DIR), $(UTILS_FILES)) 
OBJ_UTILS		= $(UTILS:.c=.o)

#RULES AND COMMANDS
all:			$(NAME)

%.o:			%.c Makefile $(INCLUDE)
				$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME):		$(OBJ_UTILS) $(OBJ_SRCS)	
				$(CC) $(CFLAGS) $(OBJ_UTILS) $(OBJ_SRCS) -o $(NAME)

clean:
				$(RM) $(OBJ_UTILS) $(OBJ_SRCS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY: 		all clean fclean re
