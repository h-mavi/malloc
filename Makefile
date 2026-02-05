ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$HOSTTYPE.so
SOURCES = malloc.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

OBJ_DIR = obj
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

LIBFT = libft/libft.a
LIBFT_DIR = libft/

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJECTS) $(LIBFT)
	@echo "Compiling $(NAME)"
	cp $(LIBFT) $(NAME)
	ar -rcs $(NAME) $(OBJECTS)
	ln -s $(NAME) libft_malloc.so

test : $(OBJECTS) $(LIBFT)
	$(CC) $(OBJECTS) $(LIBFT) $(CFLAGS)
	
clean:
	@rm -f $(OBJECTS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f a.out
	$(MAKE) fclean -C $(LIBFT_DIR)

all : $(NAME)
re : fclean all

.PHONY: all test clean fclean re
.SILENT: