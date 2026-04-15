NAME = mini_serv
NAME_BNS = mini_serv_clean

CPP_FLAGS = -Wall -Werror -Wextra -g3
CC = cc

SRC_DIR		=	./
SRC_NAME	=	mini_serv.c
BNS_NAME 	=	mini_serv_clean.c

OBJ_DIR = obj/
OBJ_NAME_1 = $(SRC_NAME:.c=.o)
OBJ_NAME_2 = $(BNS_NAME:.c=.o)
OBJ = $(OBJ_1) $(OBJ_2)
OBJ_1 = $(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME_1))
OBJ_2 = $(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME_2))
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@mkdir -p $(dir $@)
		@$(CC) $(CPP_FLAGS) $< -c -o $@
		@echo "\033[1;36m Compiled" $(*F)

%.o:%.c
		@$(CC) $(CPP_FLAGS) $< -c -o $@
		@echo "\033[1;36m Compiled" $<

$(NAME): $(OBJ)
		@c++ $(CPP_FLAGS) -o $(NAME) $(OBJ_1)
		@c++ $(CPP_FLAGS) -o $(NAME_BNS) $(OBJ_2)
		@echo "\033[1;32m Executable" $(NAME) "created"
		@echo "\033[1;32m Executable" $(NAME_BNS) "created"

clean:
		@rm -rf $(OBJ_DIR)
		@echo "\033[1;31m Deleted all object files"

fclean: clean
		@rm -f $(NAME)
		@rm -f $(NAME_BNS)
		@echo "\033[1;31m Deleted $(NAME)"
		@echo "\033[1;31m Deleted $(NAME_BNS)"

all: $(NAME) $(NAME_BNS)

re: fclean all