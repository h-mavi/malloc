ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
SOURCES = malloc.c utils.c check.c find.c main.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fPIC

OBJ_DIR = obj
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))

all : $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

LIBFT = libft/libft.a
PRINTF = libft/printf/libftprintf.a
LIBFT_DIR = libft/printf/

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJECTS) $(LIBFT)
	@echo "Compiling $(NAME)"
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJECTS) $(LIBFT) $(PRINTF)
	ln -s $(NAME) libft_malloc.so

test : $(OBJECTS) $(LIBFT)
	$(CC) $(OBJECTS) $(LIBFT) $(PRINTF) $(CFLAGS) -o test
	
clean:
	@rm -f $(OBJECTS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f test
	@rm -f libft_malloc.so
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY: all test clean fclean re
.SILENT: