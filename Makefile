NAME		= containers

CC			= c++
FLAGS		= -Wall -Wextra -Werror -std=c++98
RM			= rm -rf

INCS_DIR	= ./includes/
MAIN_INC	= -I$(INCS_DIR)
INCS		= $(shell find $(INCS_DIR) -type f -name "*.hpp")

SRCS_DIR 	= ./test/
SRCS		= $(shell find $(SRCS_DIR) -type f -name "*.cpp")

OBJS_DIR	= ./ft_objects/
OBJS		= $(SRCS:$(SRCS_DIR)%.cpp=$(OBJS_DIR)%.o)

OBJS_DIR2	= ./std_objects/
OBJS2		= $(SRCS:$(SRCS_DIR)%.cpp=$(OBJS_DIR2)%.o)

_CLEAR		= \033[0K\r\c
_OK			= [\033[32mOK\033[0m]
_CLEAN		= [\033[31mCLEAN\033[0m]

all: std ft

ft: $(OBJS)
		@$(CC) $(FLAGS) -o "ft_"$(NAME) $(OBJS) $(MAIN_INC)
		@echo "$(_OK) "ft_"$(NAME) compiled"

std: $(OBJS2)
		@$(CC) $(FLAGS) -DSTD -o "std_"$(NAME) $(OBJS2) $(MAIN_INC)
		@echo "$(_OK) "std_"$(NAME) compiled"

$(OBJS_DIR)%.o	: $(SRCS_DIR)%.cpp
			@mkdir -p $(OBJS_DIR)
			@echo "[..] compiling $*.cpp\r\c"
			@$(CC) $(MAIN_INC) -c $< -o $@
			@echo "$(_CLEAR)"

$(OBJS_DIR2)%.o	: $(SRCS_DIR)%.cpp
			@mkdir -p $(OBJS_DIR2)
			@echo "[..] compiling $*.cpp\r\c"
			@$(CC) $(MAIN_INC) -DSTD -c $< -o $@
			@echo "$(_CLEAR)"

clean:
	@$(RM) $(OBJS_DIR) $(OBJS_DIR2)

fclean: clean
	@$(RM) "ft_"$(NAME) "std_"$(NAME)
	@echo "$(_CLEAN) $(NAME) Executable removed!"

re: fclean all

.PHONY : clean fclean re