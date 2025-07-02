MAKEFLAGS += --no-print-directory -s

RED     = \e[31m
GREEN   = \e[32m
YELLOW  = \e[33m
RESET   = \e[0m

NAME      = libft.a
SRCS_DIR  = ./src
BUILD     = ./build
HEADER    = libft.h

SRCS := $(shell find $(SRCS_DIR) -name "*.c")
OBJS := $(patsubst $(SRCS_DIR)/%.c, $(BUILD)/%.o, $(SRCS))

CC     = cc
AR     = ar rcs
CFLAGS = -Wall -Wextra -Werror

all: $(BUILD) $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(BUILD)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I. -c $< -o $@
	@echo "  ✅ ${GREEN}libft/$<${RESET}"

$(BUILD):
	@mkdir -p $(BUILD)

clean:
	@rm -rf $(BUILD)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	@norminette $(SRCS_DIR) $(HEADER)

.PHONY: all clean fclean re norm
