NAME		= philo
SRCDIR		= .
INCDIR		= .
OBJDIR		= obj

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -g
INCLUDES	= -I$(INCDIR)

SOURCES		= main.c \
			  utils.c \
			  parsing.c \
			  init.c \
			  threads.c \
			  cleanup.c \
			  monitoring.c \
			  routine.c \

SRCS		= $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS		= $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) ready!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Removing object files..."
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g -fsanitize=thread
debug: re

valgrind: $(NAME)
	@echo "Running valgrind test..."
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 5 800 200 200 10

helgrind: $(NAME)
	@echo "Running helgrind test..."
	@valgrind --tool=helgrind ./$(NAME) 5 800 200 200 10

.PHONY: all clean fclean re debug valgrind helgrind
