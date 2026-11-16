ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
SOURCES = malloc.c utils.c check.c find.c main.c

B_NAME = libft_malloc_$(HOSTTYPE)_bonus.so
B_SOURCES = malloc_bonus.c utils_bonus.c check_bonus.c find_bonus.c #main.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fPIC

OBJ_DIR = obj
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))

B_OBJ_DIR = obj_bonus
B_OBJECTS = $(patsubst %.c,$(B_OBJ_DIR)/%.o,$(B_SOURCES))

all : $(NAME)
bonus : $(B_NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJ_DIR)/%.o: %.c
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

$(B_NAME) : $(B_OBJECTS) $(LIBFT)
	@echo "Compiling $(B_NAME)"
	$(CC) $(CFLAGS) -pthread -shared -o $(B_NAME) $(B_OBJECTS) $(LIBFT) $(PRINTF)
	ln -s $(B_NAME) libft_malloc_bonus.so

test : $(OBJECTS) $(LIBFT)
	$(CC) $(OBJECTS) $(LIBFT) $(PRINTF) $(CFLAGS) -o test

test_bonus : $(B_OBJECTS) $(LIBFT)
	$(CC) $(B_OBJECTS) $(LIBFT) $(PRINTF) $(CFLAGS) -o test_bonus
	
clean:
	@rm -f $(OBJECTS)
	@rm -f $(B_OBJECTS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(B_NAME)
	@rm -f test
	@rm -f test_bonus
	@rm -f libft_malloc.so
	@rm -f libft_malloc_bonus.so
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY: all bonus test test_bonus clean fclean re
.SILENT: