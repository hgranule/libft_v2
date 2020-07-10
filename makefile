# **************************************************************************** #
# GENERIC_VARIABLES

OBJ_DIR = build

# **************************************************************************** #
# COMPILER_OPTIONS

C_COMPILER = clang
C_STANDART = -std=c99
C_CFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra -g
C_LFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra -g

NASM_COMPILER = nasm
NASM_FORMAT = -f macho64
NASM_FLAGS = -g

# **************************************************************************** #
# UTIL TARGET DESCRIPTION

UTIL_NAME = util
UTIL_PATH = util
UTIL_FILE = ./libutil.a
UTIL_SRCS = ft_memchr.s ft_memset.s ft_memmove.s ft_strlen.s ft_memcmp.s ft_memcpy.s ft_memmem.c
UTIL_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(UTIL_SRCS))
UTIL_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(UTIL_SRCS))
UTIL_LIBS = 
UTIL_INCS = 

# **************************************************************************** #
# STRING TARGET DESCRIPTION

STRING_NAME = string
STRING_PATH = string
STRING_FILE = ./libstring.a
STRING_SRCS = str_area.c str_area_size.c str_raw.c str_find.c str_delete.c str_substr.c str_getters.c str_detach.c str_map.c str_write_fd.c str_insert.c str_new.c str_count_if.c str_erase.c str_replace.c str_append.c str_resizing.c
STRING_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(STRING_SRCS))
STRING_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(STRING_SRCS))
STRING_LIBS = 
STRING_INCS = 

# **************************************************************************** #
# GENERIC RULES

.PHONY: all re clean fclean
.DEFAULT_GOAL = all

all: $(UTIL_FILE) $(STRING_FILE) 

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(UTIL_FILE) $(STRING_FILE) 

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

$(STRING_FILE): $(STRING_OBJS)
	@ar rc $(STRING_FILE) $(STRING_OBJS)
	@ranlib $(STRING_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(STRING_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(STRING_INCS) -o $@ -c $< -MMD

$(OBJ_DIR)/%.s.o: $(STRING_PATH)/%.s
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(NASM_COMPILER) $(NASM_FLAGS) $< -o $@ $(NASM_FORMAT) -MD $(OBJ_DIR)/`basename $@ .o`.d -I$(STRING_PATH)

-include $(UTIL_DEPS) $(STRING_DEPS)
