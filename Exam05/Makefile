NAME = GameOfLife

CPP_FLAGS = -Wall -Werror -Wextra -g3
CC = cc

SRC_DIR		=	./
SRC_NAME	=	GameOfLife.c

OBJ_DIR = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
DEP_NAME = $(SRC_NAME:.c=.d)
OBJ = $(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@mkdir -p $(dir $@)
		@$(CC) $(CPP_FLAGS) $< -c -o $@
		@echo "\033[1;36m Compiled" $(*F)

%.o:%.c
		@$(CC) $(CPP_FLAGS) $< -c -o $@
		@echo "\033[1;36m Compiled" $<

$(NAME): $(OBJ)
		@c++ $(CPP_FLAGS) -o $(NAME) $(OBJ)
		@echo "\033[1;32m Executable" $(NAME) "created"

clean:
		@rm -rf $(OBJ_DIR)
		@echo "\033[1;31m Deleted all object files"

fclean: clean
		@rm -f $(NAME)
		@echo "\033[1;31m Deleted $(NAME)"

all: $(NAME)

re: fclean all