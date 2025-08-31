# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 00:00:00 by kutay             #+#    #+#              #
#    Updated: 2025/08/30 20:59:05 by kbatur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

# Directories
SRCDIR		= src
INCDIR		= include
OBJDIR		= obj

# Source files
SOURCES		= main.c \
			  utils.c \
			  parsing.c \
			  init.c \
			  threads.c \
			  cleanup.c \
			  monitoring.c \
			  routine.c \
			  forks.c

SRCS		= $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS		= $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -g # -fsanitize=thread
INCLUDES	= -I$(INCDIR)

# Colors for pretty output
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
WHITE		= \033[0;37m
RESET		= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CYAN)$(NAME) ready!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Removing object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

# Debug rule (for development)
debug: CFLAGS += -g -fsanitize=thread
debug: re

# Valgrind test rule
test: $(NAME)
	@echo "$(PURPLE)Running valgrind test...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 5 800 200 200

# Helgrind test rule  
helgrind: $(NAME)
	@echo "$(PURPLE)Running helgrind test...$(RESET)"
	@valgrind --tool=helgrind ./$(NAME) 5 800 200 200

.PHONY: all clean fclean re debug test helgrind
