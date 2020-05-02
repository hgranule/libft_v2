# **************************************************************************** #
# GENERIC_VARIABLES

OBJ_DIR = build

# **************************************************************************** #
# COMPILER_OPTIONS

C_COMPILER = clang
C_STANDART = -std=c99
C_CFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra
C_LFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra

NASM_COMPILER = nasm
NASM_FORMAT = -f macho64
NASM_FLAGS = 

# **************************************************************************** #
# UTIL TARGET DESCRIPTION

UTIL_NAME = util
UTIL_PATH = util
UTIL_FILE = ./libutil.a
UTIL_SRCS = ft_memchr.s ft_memset.s ft_strlen.s ft_memcmp.s ft_memcpy.s
UTIL_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(UTIL_SRCS))
UTIL_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(UTIL_SRCS))
UTIL_LIBS = 
UTIL_INCS = 

# **************************************************************************** #
# GENERIC RULES

.PHONY: all re clean fclean
.DEFAULT_GOAL = all

all: $(UTIL_FILE) 

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(UTIL_FILE) 

re: fclean all

$(UTIL_FILE): $(UTIL_OBJS)
	@ar rc $(UTIL_FILE) $(UTIL_OBJS)
	@ranlib $(UTIL_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(UTIL_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(UTIL_INCS) -o $@ -c $< -MMD

$(OBJ_DIR)/%.s.o: $(UTIL_PATH)/%.s
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(NASM_COMPILER) $(NASM_FLAGS) $< -o $@ $(NASM_FORMAT) -MD $(OBJ_DIR)/`basename $@ .o`.d -I$(UTIL_PATH)

-include $(UTIL_DEPS)
