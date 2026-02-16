ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libmalloc_$(HOSTTYPE).so
SOURCES = malloc.c utils.c check.c find.c
# main.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

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
	cp $(LIBFT) $(NAME)
	cp $(PRINTF) $(NAME)
	ar -rcs $(NAME) $(OBJECTS)
	ln -s $(NAME) libmalloc.so

test : $(OBJECTS) $(LIBFT)
	$(CC) $(OBJECTS) $(LIBFT) $(PRINTF) $(CFLAGS) -o test
	
clean:
	@rm -f $(OBJECTS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f test
	@rm -f libmalloc.so
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY: all test clean fclean re
.SILENT: