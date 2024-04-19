# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 19:49:52 by simarcha          #+#    #+#              #
#    Updated: 2024/04/19 20:24:54 by simarcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra
NAME				= pipex
RM					= rm -rf

#FILES AND PATHS
#HEADER
INCLUDE_DIR			= inc/
INCLUDE_FILES		= pipex.h \
					get_next_line.h
INCLUDE				= $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))

#UTILS - The annexes functions that I used for this project
UTILS_DIR			= utils/
UTILS_FILES			= get_next_line.c \
					ft_split.c \
					ft_split_for_slash.c \
					libft_functions.c 
UTILS				= $(addprefix $(UTILS_DIR), $(UTILS_FILES))
OBJ_UTILS			= $(UTILS:.c=.o)

#SRCS - Where the main files for this project are located
SRCS_DIR			= srcs/
SRCS_FILES			= pipex4.c \
					create_command.c \
					manage_heredoc.c
SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJ_SRCS			= $(SRCS:.c=.o)

#LIBFT
#LIBFT_DIR			= utils/ft_printf/libft/
#LIBFT_ARCHIVE		= $(addprefix $(LIBFT_DIR), libft.a)
#
#FT_PRINTF
FT_PRINTF_DIR		= utils/ft_printf/
FT_PRINTF_ARCHIVE	= $(addprefix $(FT_PRINTF_DIR), libftprintf.a)

#RULES AND COMMANDS
all:				$(FT_PRINTF_ARCHIVE) $(NAME)

%.o:				%.c Makefile $(INCLUDE)
					$(CC) $(CFLAGS) -c $< -o $@

#$(NAME):			$(OBJ_SRCS) $(LIBFT_ARCHIVE) $(FT_PRINTF_ARCHIVE) Makefile
#					$(CC) $(CFLAGS) $(OBJ_SRCS) -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) -lft -lftprintf -o $(NAME)
#
$(NAME):			$(OBJ_UTILS) $(OBJ_SRCS) $(FT_PRINTF_ARCHIVE) Makefile
					$(CC) $(CFLAGS) $(OBJ_UTILS) $(OBJ_SRCS) -L$(FT_PRINTF_DIR) -lftprintf -o $(NAME)

#$(LIBFT_ARCHIVE):
#					@$(MAKE) -s -C $(LIBFT_DIR)
#					@echo "Compiled $(LIBFT_ARCHIVE)."
#
$(FT_PRINTF_ARCHIVE):
					@$(MAKE) -s -C $(FT_PRINTF_DIR)
					@echo "Compiled $(FT_PRINTF_ARCHIVE)."

clean:
				    @echo "\033[1;31m\033[1mDeleting every object files\033[0m"
					@echo "\033[1mCleaning the object srcs files\033[0m"
					$(RM) $(OBJ_UTILS) $(OBJ_SRCS)
					@echo ""
					@echo "\033[1mCleaning the ft_printf object files\033[0m"
					@$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean:				clean
				    @echo "\033[1;31m\033[1mDeleting the executable and archive files\033[0m"
					$(RM) $(NAME)
					@echo ""
					@echo "\033[1;31m\033[1mCleaning the ft_printf object and archive files\033[0m"
					$(MAKE) fclean -C $(FT_PRINTF_DIR)

re:					fclean all

.PHONY:				all clean fclean re
