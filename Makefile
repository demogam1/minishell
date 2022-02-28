NAME = minishell

SRC_DIR = src/
INC_DIR = inc/

DISPLAY_DIR = $(addprefix ${SRC_DIR}, display/)
LEXING_DIR = $(addprefix ${SRC_DIR}, lexing/)
EXEC_DIR = $(addprefix ${SRC_DIR}, execution/)
PARSING_DIR = $(addprefix ${SRC_DIR}, parsing/)
UTILS_DIR = $(addprefix ${SRC_DIR}, utils/)

SRC = main.c
SRC_DISPLAY =	errors.c \
				prompt.c \
				signals.c 
SRC_EXEC =	binaries.c \
			builtins_cmd.c \
			builtins_cmd1.c \
			builtins_redir.c \
			builtins_left_redir.c \
			builtins.c \
			export_utils.c \
			export_utils1.c \
			export_utils2.c \
			export_utils3.c \
			export_utils4.c \
			export_utils5.c \
			export_utils6.c \
			get_tab.c \
			left_redir.c \
			path.c	\
			pipes.c \
			redirections.c \
			right_redir.c
SRC_LEXING =	environment.c \
				lexer.c \
				lexing_utils.c \
				token.c
SRC_PARSING =	ft_split_pipe.c \
				parser.c \
				trees.c
SRC_UTILS =	debug_funcs.c \
			free_stuffs.c \
			ft_itoa.c \
			ft_split.c \
			get_next_line_utils.c \
			get_next_line.c \
			utils.c \
			utils2.c \
			utils3.c \
			utils4.c \
			utils5.c

SRCS = $(addprefix ${SRC_DIR}, ${SRC})
SRCS_DISPLAY = $(addprefix ${DISPLAY_DIR}, ${SRC_DISPLAY})
SRCS_LEXING = $(addprefix ${LEXING_DIR}, ${SRC_LEXING})
SRCS_EXEC = $(addprefix ${EXEC_DIR}, ${SRC_EXEC})
SRCS_PARSING = $(addprefix ${PARSING_DIR}, ${SRC_PARSING})
SRCS_UTILS = $(addprefix ${UTILS_DIR}, ${SRC_UTILS})
SRCS_ALL = ${SRCS} ${SRCS_DISPLAY} ${SRC_EXEC} ${SRCS_PARSING} ${SRC_UTILS}

OBJ = $(SRCS:.c=.o)
OBJ_DISPLAY = ${SRCS_DISPLAY:.c=.o}
OBJ_LEXING = ${SRCS_LEXING:.c=.o}
OBJ_EXEC = ${SRCS_EXEC:.c=.o}
OBJ_PARSING = ${SRCS_PARSING:.c=.o}
OBJ_UTILS = ${SRCS_UTILS:.c=.o}
OBJS = ${OBJ} ${OBJ_DISPLAY} ${OBJ_LEXING} ${OBJ_EXEC} ${OBJ_PARSING} ${OBJ_UTILS}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

UNAME = $(shell uname -s)
ifeq (${UNAME}, Linux)
	LIB_RDL = -lreadline
endif
ifeq (${UNAME}, Darwin)
	LIB_RDL = libreadline.a
endif

TEXT = "My job is done. Now it's up to you.\n"
TEXT2 = " Created!\n"
TEXT3 = " deleted!\n"
TEXT4 = "Obj"

%.o: %.c
		@printf "\033[0;31m"
		@printf "Please wait... $@\r"
		@${CC} $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
		cp ./readline/libreadline.a ./
		@${CC} $(CFLAGS) $(OBJS) ${LIB_RDL} -lncurses -o $(NAME)
		@printf "\n"
		@printf "\033[0m"$(NAME)$(TEXT2)

all:
	@$(MAKE) -j $(NAME)
	@printf "\033[33m"$(TEXT)"\033[0m"

clean:
	@rm -rf $(OBJS)
	@printf "\033[0;31m"$(TEXT4)$(TEXT3)

fclean:	clean
	@rm -rf $(NAME)
	@rm -rf libreadline.a
	@printf "\033[0m"$(NAME)$(TEXT3)

re: fclean all

.PHONY: all, clean, fclean, re
