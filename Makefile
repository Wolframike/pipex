# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/21 05:02:15 by misargsy          #+#    #+#              #
#    Updated: 2023/10/30 18:03:10 by misargsy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS =	pipex.c \
		ppx_utils.c \
		ppx_get_path.c \
		ppx_here_doc.c

NAME = pipex
LIBFT = libft.a

OBJS = $(SRCS:.c=.o)

CHECK		= \033[32m[✔]\033[0m
BLUE		= \033[1;34m
RESET		= \033[0m

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Compiling pipex... $(RESET)"
	@cc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(CHECK) $(RESET)"
	@clear

$(LIBFT):
	@echo "$(BLUE)Compiling libft... $(RESET)"
	@make -C libft
	@mv libft/libft.a .
	@echo "$(CHECK) $(RESET)"

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Removing objects and libraries... $(RESET)"
	@rm -f $(OBJS) $(LIBFT)
	@make clean -C libft
	@echo "$(CHECK) $(RESET)"

fclean: clean
	@echo "$(BLUE)Removing executables... $(RESET)"
	@rm -f $(NAME) $(LIBFT)
	@echo "$(CHECK) $(RESET)"

re:	fclean	all

.PHONY: all bonus clean fclean re
